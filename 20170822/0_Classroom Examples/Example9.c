#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	pid=fork();
	switch(pid)
	{
		case -1:printf("Message\n");
				break;
		case 0:	sleep(5);
				printf("%d\n",getppid());
				break;
		case 1: break;
	}
	return 0;
}

/*
After a little while it prints 1 which is Pid of INIT i.e. the child becomes Orphan and the parent of all orphan processes is INIT.
If failed fork is seen, Message will be printed.
But for parent it will just break the switch block
*/