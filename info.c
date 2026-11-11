/*
* Author: Michael Johnston
* Assignment: Lab9 System Calls
* File: info.c
* Section: 121
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

void getMyTime();

int main(int argc, char* argv[])
{
    //irrelevant
    getMyTime();
    //get current time in nanoseconds
    struct timespec tn;
    if (clock_gettime(CLOCK_REALTIME, &tn) == -1) {
               perror("clock_gettime");
               exit(EXIT_FAILURE);
    }
    long myNanoSec = tn.tv_nsec;
    printf("Current time in nanoseconds: %ld\n",myNanoSec);
    
    //system info
    //uname populate utsname struct with machine info
    struct utsname machine;
    if (uname(&machine)==-1){
        perror("uname");
        exit(EXIT_FAILURE);
    }
    printf("Operating System: %s\n",machine.sysname);
    printf("System's release: %s\n",machine.release);
    printf("system's version: %s\n",machine.version);
    printf("Hardware: %s\n",machine.machine);
    //processers
    printf("Number of processers: %d\n", get_nprocs());
    //Memory
    struct sysinfo info;
    sysinfo(&info);
    //int pageMem = getpagesize();
    printf("Memory: %ld bytes\n",info.totalram);
    printf("Free Memory: %ld bytes\n",info.freeram);

    return 0;
}

//get current time
//did this by accident but still neat
void getMyTime(){
    struct timespec ts;
    //get time
    //CLOCK_REALTIME: seconds since 1970 January 1 00:00 UTC

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
               perror("clock_gettime");
               exit(EXIT_FAILURE);
    }
    //time values;
    long minutes = 60;
    long hours = 60*minutes;
    long days = 24*hours;
    //long weeks = 7*days;
    //long months = 30*days;
    //long years = 12*months;
    ///getting current time
    long myTime = ts.tv_sec;
    char tz[4] = "am";
    long double myHours = ((myTime % days) / (hours)) - 6;
    //leave only hours, get number of hours, minus 6 for CST conversion;
    if(myHours>12){
        myHours = myHours - 12;
        strcpy(tz,"pm");
    }
    long double myMinutes = (myTime % hours) / (minutes);
    long double mySeconds = (myTime % minutes);
    printf("%02Lg:%02Lg:%02Lg %s\n",myHours,myMinutes,mySeconds,tz);

}