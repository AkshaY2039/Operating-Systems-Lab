// Example 2 for understanding execv
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid;
	char *argv[]={"ls","-al","/home/akshay/Desktop/",NULL}; //storing into argument vector
	pid=fork(); //forking a new prcess
	if(pid==0) //for child process...
		execv("/bin/ls",argv); //execv call ... image gets over written
	else //for parent process...
		printf("\nThis is Parent\n");
	printf("\nCommon\n"); //only to the parent due to exec
	return 0;
}