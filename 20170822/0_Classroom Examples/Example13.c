#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	if(fork()&&fork())
		fork();
	if(fork()||fork())
		fork();
	printf("HI GUYS\n");
	return 0;
}

/*
Output:
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
akshay@Kumar ~/Desktop/SEM5LAB/OS-P/20170822/Classroom Examples $ HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
HI GUYS
i.e. 20 processes in all
*/