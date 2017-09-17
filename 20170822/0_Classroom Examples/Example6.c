// Example 6 for forking in a loop and understanding the tree
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	for(int i=0;i<3;i++) //for loop
	{
		fork(); //fork1 inside loop
		printf("*%d\n",i);
	}
	return 0;
}
