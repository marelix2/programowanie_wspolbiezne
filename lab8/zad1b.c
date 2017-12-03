#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
void *funkcja(){}
 
int main()
{
    int i;
    struct timespec bf,af;
    clock_gettime(CLOCK_MONOTONIC, &bf);
    pthread_t tab[100];
 
    for (i=0;i<100;i++){
 
        if(pthread_create(&tab[i],NULL,funkcja,NULL)>0){
            printf("Blad tworzenia watku \n");
        }
 
    }
    for(i=0;i<100;i++){
        pthread_join(tab[i],NULL);
    }  
 
    clock_gettime(CLOCK_MONOTONIC, &af);
    printf("czas: %ld nanosekund \n",af.tv_nsec-bf.tv_nsec);        
 
 
    return 0;    
}