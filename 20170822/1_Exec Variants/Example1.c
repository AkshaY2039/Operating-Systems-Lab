#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid==0)
		execl("/bin/ls", "ls", "-a","/home/akshay/Desktop",NULL);
	else
		printf("\nThis is Parent\n");
	return 0;
}