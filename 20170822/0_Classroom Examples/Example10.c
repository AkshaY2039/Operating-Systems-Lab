// Example 10 for forking one after another and understanding how the PC relation is built
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() // main module
{
	printf("Hello 1\n");
	fork(); // fork1
	printf("Hello 2\n");
	fork(); // fork2
	printf("Hello 3\n");
	return 0;
}
