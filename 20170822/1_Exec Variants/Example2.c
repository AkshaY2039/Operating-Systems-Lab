#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	char *argv[]={"ls","-al","/home/akshay/Desktop/",NULL};
	pid=fork();
	if(pid==0)
		execv("/bin/ls",argv);
	else
		printf("\nThis is Parent\n");
	return 0;
}