#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	for(int i=0;i<2;i++)
	{
		if(fork()==0)
			printf("Hello\n");
	}
	//printf("Welcome\n");
	return 0;
}

/*
Total 4 processes and 3 child so 3 Hello printed
*/