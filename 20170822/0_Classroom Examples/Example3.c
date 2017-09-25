// Example 3 for forking seperately in child
// use of wait and error log
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid;
	pid=fork(); //fork new process
	if(pid<0) //if fork fails
		fprintf(stderr,"Failed Fork");
	else
		if(pid==0) //for child process
		{
			fork(); //another for in child
			printf("OS Course\n");
		}
		else
			if(pid>0) //for parent process
			{
				wait(NULL); //wait for child process
				printf("IIITDM\n");
			}
	printf("Kancheepuram\n"); //common to all processes
	return 0;
}
