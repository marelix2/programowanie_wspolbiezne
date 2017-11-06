//zad3a
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <errno.h>
extern int errno;
#define FIFO1 "/tmp/fifozad2"
main()
{

mknod(FIFO1,S_IFIFO|0666,0);

char buff[]="ala ma kota a kot ma ale";
int fifo;
if ((fifo = open(FIFO1, O_WRONLY,O_NDELAY )) < 0)
    perror("nie moze otworzyc fifo1 do pisania");
if (strlen(buff) != write(fifo,buff,strlen(buff)))
    perror("blad zapisu do fifo");

close(fifo);
exit(0);
} 



