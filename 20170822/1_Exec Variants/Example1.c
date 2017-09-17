// Example 1 for understanding execl
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid;
	pid=fork(); //forking a new prcess
	if(pid==0) //for child process...
		execl("/bin/ls", "ls", "-a","/home/akshay/Desktop",NULL); //execl call ... image gets over written
	else //for parent process...
		printf("\nThis is Parent\n");
	printf("\nCommon\n"); //only to the parent due to exec
	return 0;
}