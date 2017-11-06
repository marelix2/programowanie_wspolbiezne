//zad2b
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>



#define FIFO1 "/tmp/fifo.1"
main()
{
char buff[512];
int fifo,i=0;
if ((fifo = open(FIFO1, O_RDONLY, O_NDELAY )) < 0)
    perror("nie moze otworzyc fifo1 do pisania");

int bytes =  read(fifo,buff,sizeof(buff));
while (i < bytes){
printf("%c",buff[i]);
i++;
};
printf("\n");
exit(0);    
}
