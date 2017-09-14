#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	for(int i=0;i<=3;i++)
	{
		fork();
		printf("*\n");
	}
	//printf("Hello\n");
	return 0;
}

/*
Output
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
akshay@Kumar ~/Desktop/SEM5LAB/OS-P/20170822/Classroom Examples $ *
*
*
*
*
*
i.e. 30 times * an 16 processes in all
*/