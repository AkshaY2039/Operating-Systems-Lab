// Zombie Process Creation using Fork
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid; //variable of type pid_t
	pid=fork(); //forking a new process
	if(pid<0) //if fork fails...
		printf("failed fork\n");
	else
		if(pid==0) //for the child process...
		{
			printf("Child Process Here\n");
			sleep(1); //sleep for one second
			printf("Me Process %d Child to Process %d am dying.\n",getpid(),getppid()); //child dies now
		}
		else //for the parent process...
			{
				printf("Parent Process Here\n");
				sleep(5); //sleep for 5 seconds
				printf("My Child Process %d died so am a Zombie now\n",pid); //child process dies so parent's a zombie now
			}
	return 0;
}