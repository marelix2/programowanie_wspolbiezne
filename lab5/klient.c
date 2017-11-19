#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#define KAMIEN 0
#define PAPIER 1
#define NOZYCE 2
#define NENOUGHTREPORTS 3
#define STATS 4
#define CONNECTION 5
#define ROZLACZENIE 6
#define TRUE 1
#define FALSE 0
typedef struct msgStruct{
long mtype;
int pid;
int messageType;
int place;
int numberOfPlayers;
int points;
} Msg;
typedef struct statStruct{
int points;
int place;
int pid;
int reports;
int symbol;
int used;
} Stats;

int ipcId;
Msg message;
int msgSize=sizeof(Msg)-sizeof(long);
Stats stats[2];
int counter,ture;

void zakonczenie_programu(int nr_sig)
{
message.mtype=1;
message.pid=getpid();
message.messageType=ROZLACZENIE;
if(msgsnd(ipcId,&message,msgSize,0)!=0)
{
perror("Blad zapisu do kolejki");
} else {
printf("Zgloszenie wyslano poprawnie\n");
}
printf("Zakonczono pomyslnie program\n");
exit(0);
}

int main(){
signal(SIGINT,zakonczenie_programu);
int key=ftok("/tmp/server.c",1337);
ipcId=msgget(key,0);
if (ipcId==-1)
{
perror("Stworzenie kolejki IPC sie nie powiodlo");
exit(0);
}
message.mtype=1;
message.pid=getpid();
message.messageType=CONNECTION;
if(msgsnd(ipcId,&message,msgSize,0)!=0)
{
perror("Blad zapisu do kolejki");
exit(0);
} else {
printf("Zgloszenie wyslano poprawnie\n");
}
while(1){
int symbol=0;
do {
printf("Wybierz symbol: ");
printf("0.Kamien ");
printf("1.Papier ");
printf("2.Nozyce \n");
scanf("%d",&symbol); }
while (symbol<0 || symbol>2);
printf("Wybrales %d\n",symbol);
message.mtype=1;
message.pid=getpid();
message.messageType=symbol;
if(msgsnd(ipcId,&message,msgSize,0)!=0)
{
perror("Blad zapisu do kolejki");
exit(0);
} else {
printf("Zgloszenie wyslano poprawnie\n");
}
if(msgrcv(ipcId,&message,msgSize,getpid(),0)!=msgSize){
perror("Blad odbioru wiadomosci");
exit(0);
} else{
if (message.messageType==NENOUGHTREPORTS){
printf("Za malo zgloszen\n");
} else
if (message.messageType==ROZLACZENIE){
exit(0);
} else
{
printf("\nPunkty: %d ,",message.points);
printf("Miejsce: %d ,",message.place);
printf("Ilosc graczy: %d\n",message.numberOfPlayers);
}
}
}
return 0;
}