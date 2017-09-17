// Example 5 for forking in loop and understanding the number of processes
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	for(int i=0;i<3;i++) //loop goes 3 times
	{
		fork(); //fork1 inside loop
	}
	printf("*\n"); //common to all processes unless exec
	return 0;
}
