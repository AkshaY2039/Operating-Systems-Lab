// Example 12 for forking in loop
// Total 4 processes and 3 child so 3 Child printed
// The number of parents and Child here will help understand the forking tree
// the number of Welcome gives the total number of processes
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid;
	for(int i=0;i<2;i++) //for loop 
	{
		if((pid=fork())<0) //if fork fails
			printf("Failed\n");
		else
			if(pid==0) //if its the Child Process
				printf("Child\n");
		else
			printf("Parent\n"); //if its the Parent Process
	}
	printf("Welcome\n"); //common in all processes
	return 0;
}
