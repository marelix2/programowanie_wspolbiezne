#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
 
 
int main()
{
    int pid;
    int i;
    struct timespec bf,af;
    clock_gettime(CLOCK_MONOTONIC, &bf);
 
 
    for (i=0;i<100;i++){
       pid = fork();
       if (pid ==0 )  exit(0);
         
    }
    int j=0;
    for (j=0;j<100;j++){
        wait(NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &af);
    printf("czas: %ld nanosekund \n",af.tv_nsec-bf.tv_nsec);
 
 
    return 0;    
}