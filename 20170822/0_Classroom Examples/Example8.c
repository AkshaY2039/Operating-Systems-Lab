// Example 8 for forking and understandimg how address spaces get duplicated
// The pointer/address remains since both processes don't actually go in parallel,
// The state of memory is saved for the one waiting and so ...
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	int j=8,*i=&j;
	if(fork()) //for parent
	{
		wait(0); //wait for child
		printf("IN PARENT: %d\t%d\t%d\t%d\n",*i,&j,i,&i);
	}
	else //for child
	{
		*i=*i+10;
		printf("IN CHILD: %d\t%d\t%d\t%d\n",*i,&j,i,&i);
	}
	return 0;
}
