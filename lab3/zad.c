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
 
    const int R = 1;
    const int W = 0;
 
 
 
        if(pipe(childPipe) < 0)
            perror("Blad otwierania pipe_c\n");
        if(pipe(parentPipe) < 0)
            perror("Blad otwierania pipe_s\n");
     
        if((pid = fork()) == -1){
            perror("Nie utworzono potomka\n");
        } else {
            if(pid == 0){
                close(childPipe[R]);
                close(parentPipe[W]);
     
                if((lengthOfString = read(childPipe[W], buffor1, sizeof(buffor1))) <= 0)
                    perror("Blad odczytu \n");
     
                FILE *file = fopen(buffor1, "r");
     
                if(file == NULL){
            char blad[20] = "Blad otwarcia pliku\n";
                    if(write(parentPipe[R], blad, sizeof(blad)) != 20)
                        perror("Blad zapisu \n");
                } else {
                    while(fgets(buffor1, sizeof(buffor1), file) != NULL)
                                write(parentPipe[R], buffor1, sizeof(buffor1));
                }
     
                fclose(file);
     
                close(childPipe[W]);
                close(parentPipe[R]);
            } else {
                close(childPipe[W]);
                close(parentPipe[R]);
     
                printf("Podaj nazwe pliku: ");    
                scanf("%s", filename);
     
                if(write(childPipe[R], filename, sizeof(filename)) != sizeof(filename))
                    perror("Blad zapisu \n");
     
                while(read(parentPipe[W], buffor2, sizeof(buffor2)) > 0)
                                write(R, buffor2, strlen(buffor2));
     
                wait(NULL);
                close(childPipe[R]);
                close(parentPipe[W]);
            }
        }
     
        return 0;
    }