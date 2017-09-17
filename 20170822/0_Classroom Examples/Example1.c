// Use of PID type
// Example 1 for forking and differentiating in Parent and Child
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() // main module
{
	pid_t pid;
	pid=fork(); //forking a new process
	if(pid==0) // this is child
		printf("Child Block\n");
	else if(pid>0) // this is parent and if pid<0 will be failed fork
		printf("Parent Block\n");
	return 0;
}
