#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	for(int i=0;i<3;i++)
	{
		fork();
	}
	printf("*\n");
	return 0;
}

/*
*
*
*
*
*
*
*
*
i.e. 8 processes in all
*/
