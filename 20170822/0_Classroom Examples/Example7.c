// Example 7 for forking and understanding the number of processes under certain conditions
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	pid_t pid;
	pid=fork(); //fork1
	if(pid!=0) //in case of parent or failed fork
		fork(); //go for fork2
	fork(); //fork3
	printf("Fork Done\n");
}
