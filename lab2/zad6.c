#include <stdio.h>
#include <stdlib.h>

int main(){
	int cpid;
	int	status; 
	int i; 
	
	for(i = 0; i < 5; i++){
		if ((cpid = fork()) == -1) exit(1);
		else if (cpid == 0){
			printf("Proces potomny o pidzie %d z rodzica %d\n",getpid(),getppid());
			 
			 if(i != 4) wait(1);
			 else sleep(5);
		} else {
			printf("Proces macierzysty o pidzie %d i dziecku %d\n",getpid(),cpid);
			wait();
		}
	}

	exit(0);    
}
