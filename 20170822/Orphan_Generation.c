// Orphan Process Creation using Fork
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid; //variable of type pid_t from sys/types.h
	pid=fork(); //forking a new process
	if(pid<0) //if fork fails...
		printf("failed fork\n");
	else
		if(pid==0) //for the child process...
		{
			printf("Child Process Here\n");
			int parent=getppid(); //get parent's id
			sleep(3); //sleep for 3 seconds
			int new_parent=getppid(); //get new parent's id, which is Init (the godfather of all processes in Linux setup)
			if(parent!=new_parent) //if old parent is not the new parent...
				printf("My Parent Process %d died. I am an orphan now. God thanks process %d\n",parent,new_parent); //child is orphan now
		}
		else //for the parent process
			{
				sleep(1); //sleep for 1 second
				printf("Parent Ended\n"); //and parent dies here
			}
	return 0;
}