#include <stdio.h>
#include <stdlib.h>
#include <signal.h>



void obsluga(int signall){
	printf("Potomek sie zakonczyl, sygnal %d\n", signall);
}

int main(){
	int cpid;
	int	status;
	int i; 
	
	signal(SIGCHLD, obsluga);

	for(i = 0; i < 5; i++){
		if ((cdpid = fork()) == -1) exit(1);
		else if (cpid == 0){
			printf("Proces potomny o pidzie %d z rodzica %d\n",getpid(),getppid());
			exit(1);
		} else {
			sleep(2);
			printf("Proces macierzysty o pidzie %d i dziecku %d\n",getpid(),cpid);
		}
	}

	exit(0);    
}
