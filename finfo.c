/*
* Author: Michael Johnston
* Assignment: Lab9 System Calls
* File: finfo.c
* Section: 121
*/

// finfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if(argc > 1){
        int fd = open(argv[1], O_PATH); //grab fd through O_PATH flag //need _GNU_SOURCE for this
        if(fd == -1){
            perror("File error: ");
            return 0;
        }
        //stat
        //fstat since we got a file descriptor
        //could use stat with file path
        struct stat myStats;
        int ste = fstat(fd,&myStats);
        if(ste == -1){
            perror("stat error: ");
            return 0;
        }

        //print stats info
        //file type
            //myStats.st_mode
        //printf("Stats mode: %d\n", myStats.st_mode);
        printf("file type: ");
        switch (myStats.st_mode & S_IFMT) {
        case S_IFREG:  
            printf("Regular file\n");
            break;
        case S_IFDIR:
            printf("Directory\n");/* Directory */     break;
        case S_IFLNK:  
            printf("link\n");/* Symlink */       
            break;
        default:
            printf("Unknown\n");/* Other */         
        break;
        }
        //file permissions
        printf("file permissions: ");
            //myStats.st_mode
        //read
        if(myStats.st_mode & S_IRUSR){
            printf("read ");
        }
        //write
        if(myStats.st_mode & S_IWUSR){
            printf("write ");
        }
        //execute
        if(myStats.st_mode & S_IXUSR){
            printf("execute ");
        }
        printf("\n");
        //file owner
        printf("User ID: %d\n",myStats.st_uid);
        //file size
        printf("File size: %ld\n",myStats.st_size);
        //date and time of last modification
            //myStats.st_mtime
            struct timespec ts = myStats.st_mtim;
            struct tm *timeinfo = localtime(&ts.tv_sec); // covert to local time
            //Date
            // NOTE: tm_year is years since 1900, tm_mon is 0-indexed (0-11)
            int myYears  = timeinfo->tm_year + 1900;
            int myMonths = timeinfo->tm_mon + 1;
            int myDays   = timeinfo->tm_mday;
            printf("last modified: %d/%d/%d ",myYears,myMonths,myDays);
            //time of day
            int myHours  = timeinfo->tm_hour;
            int myMins   = timeinfo->tm_min;
            int mySecs   = timeinfo->tm_sec;
            printf("%02d:%02d:%02d\n",myHours,myMins,mySecs);
    }else{
        printf("enter file at command\n"); //program can't do anything without a file
        return 0;
    }
    
    return 0;
}