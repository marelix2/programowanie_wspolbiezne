#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include  <signal.h>
#define PERMS 0666
 
 
 
 
static struct sembuf op_lock1[1] = {
    0, -1, 0   
};
 
static struct sembuf op_unlock1[1] = {
    0, 1, 0
};
 
static struct sembuf op_lock2[1] = {
    1, -1, 0   
};
 
static struct sembuf op_unlock2[1] = {
    1, 1, 0
};
 
 
void blokuj_semafor1(int semid)
{
    if (semop(semid, &op_lock1[0], 1)<0)
        perror("blad lokowania semafora");
}
 
void odblokuj_semafor1(int semid)
{
    if (semop(semid, &op_unlock1[0], 1) < 0)
        perror("blad odlokowania semafora");
}
 
void blokuj_semafor2(int semid)
{
    if (semop(semid, &op_lock2[0], 1)<0)
        perror("blad lokowania semafora");
}
 
void odblokuj_semafor2(int semid)
{
    if (semop(semid, &op_unlock2[0], 1) < 0)
        perror("blad odlokowania semafora");
}
 
 
char *shmp;
int semid;
int shmid;
int run=1;
 
void oblsluga_zakonczenia_serwera(int nr_sig)
{
    printf("Koncze serwer\n");
    run=0;
 
    if(shmdt(shmp)<0) perror("Blad odlaczania pamieci dzielonej");
    if(semctl(semid,0,IPC_RMID,0)<0) perror("Blad usuwania zbioru semaforow");
    if(shmctl(shmid,IPC_RMID,NULL)<0) perror("Blad usuwania pamieci dzielonej");
    exit(1);
}
 
 
int main(){
    signal(SIGINT,oblsluga_zakonczenia_serwera);
    srand(getpid());
 
    shmid= shmget(ftok("serwer.c",3), sizeof(int),IPC_CREAT | IPC_EXCL | PERMS);
    if (shmid==-1){
        perror("Blad tworzenia pamieci dzielonej");
    }
 
    shmp = shmat(shmid,0, 0);
    if (shmp==NULL){
        perror("Blad dolaczania pamieci dzielonej");
 
    }
 
    semid = semget(ftok("serwer.c",3), 2, IPC_CREAT | PERMS);
    if  (semid < 0){
        perror("blad tworzenia zbioru semaforow");
    }
 
    int liczba=1;
    while(run){
 
        blokuj_semafor2(semid);
 
        int time=rand()%1000001;
        printf("Spie przez %d\n",time);
        *shmp=liczba;
        liczba++;
 
        odblokuj_semafor1(semid);
        usleep(time);
 
    }
 
 
    return 0;
}