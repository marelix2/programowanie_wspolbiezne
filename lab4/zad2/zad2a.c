#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <errno.h>
extern int errno;
#define FIFO1 "/tmp/fifo.1"
main()
{
char buff[]="ala ma kota a kot ma ale";
int fifo;
if ((fifo = open(FIFO1, O_WRONLY,O_NDELAY )) < 0)
    perror("nie moze otworzyc fifo1 do pisania");
if (strlen(buff) != write(fifo,buff,strlen(buff)))
    perror("blad zapisu do fifo");


exit(0);
}    


