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
 
 
int main(){
 
    srand(getpid());
 
    int shmid= shmget(ftok("serwer.c",3), sizeof(int),PERMS);
    if (shmid==-1){
        perror("Blad tworzenia pamieci dzielonej");
        exit(0);
    }
 
    char *shmp = shmat(shmid,0, 0);
    if (shmp==NULL){
        perror("Blad dolaczania pamieci dzielonej");
        exit(0);
    }
 
    semid = semget(ftok("serwer.c",3), 2, PERMS);
    if  (semid < 0){
        perror("blad tworzenia zbioru semaforow");
    }
 
    int liczba;
    int i;
    for(i=0;i<10;i++){
 
        odblokuj_semafor2(semid);
        blokuj_semafor1(semid);
        liczba=*shmp;
        printf("Liczba= %d\n",liczba);
        int time=rand()%1000001;
        usleep(time);
    }
    shmdt(shmp);
 
    return 0;
}
 