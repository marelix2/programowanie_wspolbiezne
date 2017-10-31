#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
int lengthOfString;
char buffor1[100];
char buffor2[100];
char filename[100];
int childPipe[2];
int parentPipe[2];
int pid;
const int R = 0;
const int W = 1;

if(pipe(childPipe) < 0)
perror("Blad otwierania pipe_c\n");

if(pipe(parentPipe) < 0)
perror("Blad otwierania pipe_s\n");

if((pid = fork()) == -1){
perror("Nie utworzono potomka\n");
} else {
if(pid == 0){
close(childPipe[W]);
close(parentPipe[R]);
if((lengthOfString = read(childPipe[R], buffor1, sizeof(buffor1))) <= 0)
perror("Blad odczytu \n");
FILE *file = fopen(buffor1, "r");
if(file == NULL){
char blad[20] = "Blad otwarcia pliku\n";
if(write(parentPipe[W], blad, strlen(blad)) != 20)
perror("Blad zapisu \n");
} else {
while(fgets(buffor1, sizeof(buffor1), file) != NULL){
//printf("wpisuje dane do Pipe rodzica \n ------------------- \n");
write(parentPipe[W], buffor1, sizeof(buffor1));
}
}
fclose(file);
close(childPipe[R]);
close(parentPipe[W]);
} else {
close(childPipe[R]);
close(parentPipe[W]);
printf("Podaj nazwe pliku: ");
scanf("%s", filename);
if(write(childPipe[W], filename, strlen(filename)+1) != strlen(filename)+1)
perror("Blad zapisu \n");
else printf("przekazano dane do Pipe procesu potomnego\n ------------------- \n");
while(read(parentPipe[R], buffor2, sizeof(buffor2)) > 0)
write(W, buffor2, strlen(buffor2));
wait(NULL);
close(childPipe[W]);
close(parentPipe[R]);
}
}
return 0;
}
