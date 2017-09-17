// Odd and Even Series generation in Parent Child Setup
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	int n; //getting the length of series to be generated from user
	printf("Enter the number 'n': ");
	scanf("%d",&n);

	pid_t pid=fork(); //forking a new process
	if(pid<0) //if fork fails...
		printf("Fork Failed\n");
	else
		if(pid==0) //for the child process...
		{
			printf("The Odd series generated here by Child:\n");
			for(int i=1;i<=n;i++) //generate all odd numbers
				printf("%d\t",i++);
			printf("\n");
		}
		else //for the parent process...
			{
				printf("Parent is waiting for child to complete...\n");
        		wait(0); //parent waits for child to finish
        		printf("The Even series generated here by Parent:\n");
				for(int i=0;i<=n;i++) //generates all even numbers
					printf("%d\t",i++);
				printf("\n");
			}
	return 0;
}