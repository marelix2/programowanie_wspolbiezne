#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <errno.h>
extern int errno;
#define FIFO1 "/tmp/fifoFirstToSec"
#define FIFO2 "/tmp/fifoSecToFirst"

#define MAXSIZE 1024
main()
{

mknod(FIFO1,S_IFIFO|0666,0);
mknod(FIFO2,S_IFIFO|0666,0);


char buffToWrite[MAXSIZE];
char buffToRead[MAXSIZE];
int fifo,fifo2;
int pid = fork();
int bytes;


if(pid ==0){

    fifo = open(FIFO1,O_RDONLY);
int i = 0;
    while(1){
if(bytes = read(fifo, buffToRead, sizeof(buffToRead))>0)
wahile( i < bytes){
printf("%s\n",buffToRead[i]);
i++;
}

}else {

    fifo2 = open(FIFO2,O_WRONLY);
    while(1){
    scanf("%s",buffToWrite);
    if (write(fifo2,buffToWrite,strlen(buffToWrite)) != strlen(buffToWrite))
            perror("nie moze otworzyc fifo1 do pisania");


        }

}


close(fifo);
close(fifo2);
//unlink(FIFO1);
//unlink(FIFO2);
exit(0);
} 