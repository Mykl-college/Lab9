/*
* Author: Michael Johnston
* Assignment: Lab9 System Calls
* File: pmod.c
* Section: 121
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
    struct timespec mySleep;
    struct timespec pauseSleep;
    mySleep.tv_nsec = (1837272638 - 999999999); // 999 999 999
    nice(10); //add 10 to its niceness value - lowers priority by 10
    int slept = nanosleep(&mySleep,&pauseSleep); //timespec for time, timespec for remaining if interuptted
    if(slept==-1){
        perror("Error: ");
    }else{
    mySleep.tv_nsec = (999999999); // twice for large number
    slept = nanosleep(&mySleep,&pauseSleep); //timespec for time, timespec for remaining if interuptted
    if(slept==-1){
        perror("Error: ");
    }else{
        printf("Goodbye\n");
    }
    }
    return 0;
}