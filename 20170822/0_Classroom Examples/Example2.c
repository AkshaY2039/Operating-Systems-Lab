// Example 2 for forking blindly n times 2^n processes
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() //main module
{
	fork(); //fork1
	fork(); //fork2
	fork(); //fork3
	printf("World\n"); //common to all processes created
	return 0;
}
