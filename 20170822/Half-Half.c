// Half half Ascending and descending sort in Parent Child Setup
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() //main module
{
	int n; //getting the size of array by user
	printf("Enter the size of array 'n': ");
	scanf("%d",&n);

	int array[n]; //getting the array data from the user
	printf("Enter the array data \n");
	for(int i=0;i<n;i++)
		scanf("%d",&array[i]);

	int tempn=n/2; //the mid index
	
	pid_t pid=fork(); //forking a new process
	if(pid<0) //if fork fails...
		printf("Fork Failed\n");
	else
		if(pid==0) //for the child process...
		{
			printf("The Descending Sort on Second Half of Array here by Child:\n");
			for(int i=tempn;i<n;i++) //sorting the rear half into Descending using Bubble Sort
				for(int j=tempn;j<n-i+tempn-1;j++)
					if(array[j]<array[j+1])
					{
						int temp=array[j];
						array[j]=array[j+1];
						array[j+1]=temp;
					}
			for(int i=0;i<n;i++) //printing the array
				if(i==tempn)
					printf("++ %d ",array[i]);
				else
					printf("%d ",array[i]);
			printf("\nChild ends\n");
		}
		else //for the parent process...
			{
				printf("Parent is waiting for child to complete...\n");
        		wait(0); //wait for the child to finish
        		printf("The Ascending Sort on First Half of Array here by Parent:\n");
				for(int i=0;i<tempn;i++) //sorting the front half into Ascending using Bubble Sort
					for(int j=0;j<tempn-i-1;j++)
						if(array[j]>array[j+1])
						{
							int temp=array[j];
							array[j]=array[j+1];
							array[j+1]=temp;
						}
				for(int i=0;i<n;i++) //printing the array
				if(i==tempn)
					printf("++ %d ",array[i]);
				else
					printf("%d ",array[i]);
				printf("\nParent ends\n");
			}
	return 0;
}