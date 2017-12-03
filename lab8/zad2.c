#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
struct argument{
    char *nazwa;
    int numer;
};
 
pthread_key_t klucz;
pthread_once_t control = PTHREAD_ONCE_INIT;
void tworzenie_klucza(){
    printf("Tworze klucz\n");
    pthread_key_create(&klucz,free);
}
 
void usuwanie_klucza(){
    printf("Usuwam klucz\n");
    pthread_key_delete(klucz);
}
 
 
void *funkcja_watku(void *arg){
    pthread_once(&control,tworzenie_klucza);
 
    struct argument *argument=arg;
    pthread_setspecific(klucz,argument->nazwa);
    pthread_mutex_unlock(&mutex);
    sleep(10); 
    printf("Czesc jestem %s;%d\n",(char*)pthread_getspecific(klucz),argument->numer);
}
 
 
 
int main()
{
    int i,j;
 
    pthread_t tab_tid[5];
 
    for (i=0;i<5;i++){
        sleep(1);
        pthread_mutex_lock(&mutex);
        struct argument arg;
        arg.numer=i+1;
        char nz[10];
        sprintf(nz,"watek nr %d",i+1);
        arg.nazwa=malloc(sizeof(nz));
        strcpy(arg.nazwa,nz);
 
        if(pthread_create(&tab_tid[i],NULL,funkcja_watku,&arg)>0){
            printf("Blad tworzenia watku \n");
        }      
    }
    for (j=0;j<5;j++){
        if(pthread_join(tab_tid[j],NULL)>0)
            printf("Blad oczekiwania na zakonczenie watku\n");
    }
    usuwanie_klucza();
    pthread_mutex_destroy(&mutex);
 
    return 0;    
}