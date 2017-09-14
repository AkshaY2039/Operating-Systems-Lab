// Odd and Even Series generation in Parent Child Setup
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int n;
	printf("Enter the number 'n': ");
	scanf("%d",&n);
	pid_t pid=fork();
	if(pid<0)
		printf("Fork Failed\n");
	else
		if(pid==0)
		{
			printf("The Odd series generated here by Child:\n");
			for(int i=1;i<=n;i++)
				printf("%d\t",i++);
			printf("\n");
		}
		else
			{
				printf("Parent is waiting for child to complete...\n");
        		wait(0);
        		printf("The Even series generated here by Parent:\n");
				for(int i=0;i<=n;i++)
					printf("%d\t",i++);
				printf("\n");
			}
	return 0;
}