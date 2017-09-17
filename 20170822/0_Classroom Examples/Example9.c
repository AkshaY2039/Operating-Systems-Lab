// Example 9 for forking and testing a Orphan Process
/*
After a little while it prints 1 which is Pid of INIT i.e. the child becomes Orphan and the parent of all orphan processes is INIT.
If failed fork is seen, Message will be printed.
But for parent it will just break the switch block
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid;
	pid=fork(); //fork1
	switch(pid)
	{
		case -1:printf("Message\n"); //failed case
				break;
		case 0:	sleep(5); //child case sleep for 5 seconds
				printf("%d\n",getppid()); //get parent pid
				break;
		case 1: break; //parent case break
	}
	return 0;
}
