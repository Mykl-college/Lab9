/*
* Author: Michael Johnston
* Assignment: Lab9 System Calls
* File: pinfo.c
* Section: 121
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <errno.h>


int main(int argc, char* argv[])
{
    //get process id
    pid_t t_pid;
    if(argc>1){
        t_pid = (pid_t) atoi(argv[1]);
        //if pid dne,
        //print error, exit
        if (kill(t_pid, 0) != 0) { // will only check if valid pid, no signal sent
            printf("process id is not valid\n"); 
            //end
            return 0;
        }
    }else{
        //if none, print current pid
        t_pid = getpid();
    }
    //print
        //priority
        errno = 0;
        int prio = getpriority(PRIO_PROCESS,t_pid);
        //error check - getpriority can result a -1 as a succesful return
        if (prio == -1 && errno != 0) {
            printf("Error getting priority: %s\n", strerror(errno));
        }else{
            printf("Priority: %d\n",prio);
        }
        //scheduling method
        int policy = sched_getscheduler(t_pid);
        //error
        if (policy == -1) {
            perror("Failed to get scheduler");
        }else{
        //response
        if(policy == SCHED_OTHER) {
            printf("Standard time-sharing policy (SCHED_OTHER)\n");
        }else 
        if(policy == SCHED_FIFO) {
            printf("Real-time FIFO policy (SCHED_FIFO)\n");
        }else 
        if(policy == SCHED_RR) {
            printf("Real-time Round Robin policy (SCHED_RR)\n");
        }else{
            printf("Other policy: %d\n", policy);
        }
        }
    return 0;
}