#include <stdio.h>
#include <stdlib.h>
int main(){
int cpid;
int    status;
int i;
for(i = 0; i < 5; i++){
if ((cpid = fork()) == -1) exit(1);

if (cpid == 0){
printf("Proces potomny o pidzie %d z rodzica %d\n",getpid(),getppid());
if(i != 4) wait(1);
else sleep(5);
}
else {
wait(NULL);
exit(1);

}
}
exit(0);
}