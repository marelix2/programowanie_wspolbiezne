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
void sort(){
int i, j, tempPoints,tempPid,tempUsed,tempReports,tmpCounter;
for (i = 0; i<2-1; i++)
{
for (j=0; j<2-1-i; j++)
{
if (stats[j].points < stats[j+1].points)
{
tempPoints = stats[j+1].points;
stats[j+1].points = stats[j].points;
stats[j].points = tempPoints;
tempPid=stats[j+1].pid;
stats[j+1].pid=stats[j].pid;
stats[j].pid=tempPid;
tempUsed=stats[j+1].used;
stats[j+1].used=stats[j].used;
stats[j].used=tempUsed;
tempReports=stats[j+1].reports;
stats[j+1].reports=stats[j].reports;
stats[j].reports=tempReports;
}
}
}
for (i=0;i<2;i++){
if (stats[i].used==TRUE){
stats[i].place=tmpCounter;
tmpCounter++;
printf("PID: %d, place: %d, points %d\n",stats[i].pid,stats[i].place,stats[i].points);
}
}
}
void fileExit(int nr_sig)
{
int i;
for (i=0;i<2;i++){
if(stats[i].pid!=0){
message.messageType=ROZLACZENIE;
message.mtype=stats[i].pid;
msgsnd(ipcId,&message,msgSize,0);
}
}
msgctl(ipcId,IPC_RMID,NULL);
exit(0);
}

void playerJoin(){
if(counter==2){
printf("cannot join , lack of place \n");
message.messageType=ROZLACZENIE;
message.mtype=message.pid;
msgsnd(ipcId,&message,msgSize,0);
} else {
int i;
for (i=0;i<2;i++){
if (stats[i].pid==0)
{
printf("player %d join\n",message.pid);
stats[i].pid=message.pid;
stats[i].used=TRUE;
break;
}
}
counter++;
}
}

void playerExit(){
int i;
for (i=0;i<2;i++){
if (stats[i].pid==message.pid)
{
printf("player %d leave\n",message.pid);
stats[i].pid=0;
stats[i].used=FALSE;
stats[i].points=0;
stats[i].place=0;
break;
}
}
counter--;
}

void sendResults(){
int i;
for (i=0;i<2;i++){
if(stats[i].reports==TRUE){
message.messageType=STATS;
message.mtype=stats[i].pid;
message.place=stats[i].place;
message.numberOfPlayers=counter;
message.points=stats[i].points;
if(msgsnd(ipcId,&message,msgSize,0)!=0){
perror("Blad wyslania messagei");
}
stats[i].reports=FALSE;
}
}
}

void countPoints(){
int points;
int i;
int counterK=0;
int counterN=0;
int counterP=0;
for (i=0;i<2;i++){
if (stats[i].reports==TRUE){
if (stats[i].symbol==KAMIEN) counterK++;
else if (stats[i].symbol==PAPIER) counterP++;
else if (stats[i].symbol==NOZYCE) counterN++;
}
}
for (i=0;i<2;i++){
if (stats[i].reports==TRUE){
if(stats[i].symbol==KAMIEN){
points=counterN-counterP;
stats[i].points+=points;
printf("player: %d got %d points\n",stats[i].pid,points);
}
if(stats[i].symbol==PAPIER){
points=counterK-counterN;
stats[i].points+=points;
printf("player: %d got %d points\n",stats[i].pid,points);
}
if(stats[i].symbol==NOZYCE){
points=counterP-counterK;
stats[i].points+=points;
printf("player: %d got %d points\n",stats[i].pid,points);
}
}
}
}
int main(){
signal(SIGINT,fileExit);
int key=ftok("/tmp/server.c",1337);
ipcId=msgget(key,IPC_CREAT|0666);
if (ipcId==-1)
{
perror("failed");
exit(0);
}
while(1){
sleep(10);
printf("\n\n Ture: %d\n\n",ture);
ture++;
int notCounter=0;
while(msgrcv(ipcId,&message,msgSize,1,IPC_NOWAIT)==msgSize){
if (message.messageType==CONNECTION){
playerJoin();
}
else if (message.messageType==ROZLACZENIE){
playerExit();
} else{
int i;
for (i=0;i<2;i++){
if (stats[i].pid==message.pid)
{
printf("notification to player %d : ",message.pid);
stats[i].symbol=message.messageType;
if (stats[i].symbol==PAPIER) printf("papier\n");
if (stats[i].symbol==KAMIEN) printf("kamien\n");
if (stats[i].symbol==NOZYCE) printf("nozyce\n");
stats[i].reports=TRUE;
break;
}
}
notCounter++;
}
}
if (notCounter==0){
printf("Brak zgloszen\n");
} else if(notCounter==1){
printf("Tylko jedno zgloszenie\n");
int pid_odbiorcy=message.pid;
message.messageType=NENOUGHTREPORTS;
message.mtype=pid_odbiorcy;
if(msgsnd(ipcId,&message,msgSize,0)!=0){
perror("Blad wyslania messagei");
}
} else
{
printf("Wystarczajaca liczba zgloszen\n");
countPoints();
sort();
sendResults();
}
}
return 0;
}