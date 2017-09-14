//Use of PID type
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==0)
		printf("Child Block\n");
	else if(pid>0) //since <0 will be failed fork
		printf("Parent Block\n");
	return 0;
}

//noticed that by default Parent Block is printed first