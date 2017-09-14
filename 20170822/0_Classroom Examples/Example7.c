#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid!=0) // in case of failed fork also it may go for a fork
		fork();
	fork();
	printf("Fork Done\n");
}

//6 Processes in total