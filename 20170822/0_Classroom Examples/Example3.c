//use of wait and error log
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
		fprintf(stderr,"Failed Fork");
	else
		if(pid==0)
		{
			fork();
			printf("OS Course\n");
		}
		else
			if(pid>0)
			{
				wait(NULL);
				printf("IIITDM\n");
			}
	printf("Kancheepuram\n");
	return 0;
}

//output seems to be:
/*
OS Course
Kancheepuram
OS Course
Kancheepuram
IIITDM
Kancheepuram
but when there is no wait call (Parent doesn't wait for the child and the child becomes orphan)
IIITDM
Kancheepuram
OS Course
Kancheepuram
OS Course
Kancheepuram
*/