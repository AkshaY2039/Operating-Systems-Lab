// Orphan Process Creation
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
			int parent=getppid();
			sleep(3);
			int new_parent=getppid();
			if(parent!=new_parent)
				printf("My Parent Process %d died. I am an orphan now. God thanks process %d\n",parent,new_parent);
		}
		else
			{
				sleep(1);
				printf("Parent Ended\n");
			}
	return 0;
}