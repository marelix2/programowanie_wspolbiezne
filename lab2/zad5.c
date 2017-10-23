
#include <stdio.h>
#include <stdlib.h>
int main(){
int cpid;
int    status;
int i,j;
for(i = 0; i < 5; i++){
if ((cpid = fork()) == -1) exit(1);
else if (cpid == 0){
printf("Proces potomny o pidzie %d z rodzica %d\n",getpid(),getppid());
sleep(5);
exit(2);
}
}
for(j =0; j<5; j++) wait(NULL);
exit(0);
}
