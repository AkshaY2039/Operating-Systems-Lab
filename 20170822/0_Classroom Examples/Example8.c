#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int j=8,*i=&j;
	if(fork())
	{
		wait(0);
		printf("%d\n",*i);
	}
	else
	{
		*i=*i+10;
		printf("%d\t",*i);
	}
	return 0;
}

//output is 18	8 which means even address space for pointers is different in Parent and child.