// Zombie Process Creation
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
		printf("failed fork\n");
	else
		if(pid==0)
		{
			printf("Child Process Here\n");
			sleep(1);
			printf("Me Process %d Child to Process %d am dying.\n",getpid(),getppid());
		}
		else
			{
				printf("Parent Process Here\n");
				sleep(5);
				printf("My Child Process %d so am a Zombie now\n",pid);
				printf("Parent Ended\n");
			}
	return 0;
}