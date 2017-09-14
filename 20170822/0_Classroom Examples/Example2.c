//Blind Fork 2^n processes
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	fork();
	fork();
	fork();
	printf("World\n");
	return 0;
}