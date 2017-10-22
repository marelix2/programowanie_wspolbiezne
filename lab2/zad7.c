#include <stdio.h>
#include <stdlib.h>
#include <signal.h>



void obsluga(int nr){
	printf("Potomek sie zakonczyl\n");
}

int main(){
	int childpid;
	int	status;
	int i; 
	
	signal(SIGCHLD, obsluga);

	for(i = 0; i < 5; i++){
		if ((childpid = fork()) == -1){exit(1);
		else if (childpid == 0){
			printf("Proces potomny o pidzie %d z rodzica %d\n",getpid(),getppid());
			exit(1);
		} else {
			printf("Proces macierzysty o pidzie %d i dziecku %d\n",getpid(),childpid);
		}
	}

	exit(0);    
}
