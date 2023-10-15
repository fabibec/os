#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int val = 0;

int main(){
	pid_t pid;

	printf("val init: %d\n", val);

	pid = fork();

	if(pid < 0){
		printf("err\n");
	}else if(pid == 0){
		val = 1;
	
		printf("child pid: %d\n", getpid());
		printf("val in child proc: %d\n", val);
	}else{
		wait(NULL);
		printf("parent pid: %d\n", getpid());
		printf("val after child proc: %d\n", val);
	}

	return 0;		
}
