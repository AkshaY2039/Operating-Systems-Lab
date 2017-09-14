#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	for(int i=0;i<3;i++)
	{
		fork();
		printf("*%d\n",i);
	}
	return 0;
}

/*
*0
*1
*0
*1
*2
*1
*2
*2
*1
*2
*2
*2
*2
*2
		or
*0
*1
*0
*2
*1
*1
*2
*2
*1
*2
*2
*2
*2
*2
		or
*0
*1
*2
*1
*2
*2
*0
*1
*2
*1
*2
*2
*2
*2
such output is received
*/