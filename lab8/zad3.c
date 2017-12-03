#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
 
void czyszczenie(void *arg){
 
    int *n=(int *)arg;
    printf("Czyszcze numer %d\n",*n);
 
}
 
 
void *funkcja_watku1(void *arg){
    printf("Startuje watek 1\n");
    pthread_t tid=*(pthread_t *) arg;
    int parametr=0;
    pthread_cleanup_push(czyszczenie,&parametr);
    sleep(2);
    printf("Watek 1 po pierwszym sleep\n");
    pthread_cancel(tid);
    sleep(2);
    printf("Watek 1 po drugim sleep\n");
    pthread_cancel(tid);
    pthread_cleanup_pop(0);
 
 
}
 
void *funkcja_watku2(void *arg){
    printf("Startuje watek 2\n");
    int old;
    int parametr=1;
    pthread_cleanup_push(czyszczenie,&parametr);
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old);
    sleep(3);
    printf("Watek 2 po pierwszym sleep\n");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old);
    sleep(2);
    printf("Watek 2 po drugim sleep\n");
    pthread_cleanup_pop(1);
}
 
 
int main()
{
    int i,j;
 
    pthread_t tid1,tid2;
 
 
    if(pthread_create(&tid2,NULL,funkcja_watku2,NULL)>0){
        printf("Blad tworzenia watku \n");
    }
    if(pthread_create(&tid1,NULL,funkcja_watku1,&tid2)>0){
        printf("Blad tworzenia watku \n");
    }
 
 
 
    if(pthread_join(tid1,NULL)>0)
        printf("Blad oczekiwania na zakonczenie watku\n");
    if(pthread_join(tid2,NULL)>0)
        printf("Blad oczekiwania na zakonczenie watku\n");
 
 
 
    return 0;    
}