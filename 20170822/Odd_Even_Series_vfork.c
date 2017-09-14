// Odd and Even Series generation in Parent Child Setup
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int n,i=0;
	printf("Enter the number 'n': ");
	scanf("%d",&n);
	pid_t pid=vfork();
	if(pid<0)
		printf("Fork Failed\n");
	else
		if(pid==0)
		{
			while(i<n)
				if(i%2==1)
					printf("%d(C) ",i++);
			exit(0);
		}
		else
			{
				while(i<n)
					if(i%2==0)
						printf("%d(P) ",i++);
				printf("\n");
			}
	return 0;
}