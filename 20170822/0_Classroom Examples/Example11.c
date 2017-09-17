// Example 13 for forking in loop
// #processes=#Hello printed
// #processes(loop_value)=2^(loop_value(2^(fork_in _loop-1)))
// #number of stars(loop_value)=SUMMATION(1 to loop_value) processes(i)
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	int loop_value;
	printf("Enter the number of times loop should run : ");
	scanf("%d",&loop_value);
	for(int i=0;i<loop_value;i++)
	{
		fork(); //fork1 - number of fork in loop=1
		printf("*\n");
	}
	printf("Hello\n");
	return 0;
}
