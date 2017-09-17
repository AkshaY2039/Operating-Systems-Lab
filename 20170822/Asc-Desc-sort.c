// Ascending and descending sort in Parent Child Setup
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() //main module
{
	int n; //getting the size of the array
	printf("Enter the size of array 'n': ");
	scanf("%d",&n);

	int array[n]; //getting the data for the array
	printf("Enter the array data \n");
	for(int i=0;i<n;i++)
		scanf("%d",&array[i]);

	pid_t pid=fork(); //forking a new process
	if(pid<0) //if fork fails...
		printf("Fork Failed\n");
	else
		if(pid==0) //for the child process...
		{
			printf("The Ascending Sort of Array here by Child:\n"); //Sorting array into ascending order using Bubble Sort
			for(int i=0;i<n;i++)
				for(int j=0;j<n-i-1;j++)
					if(array[j]>array[j+1]) //if the next element is greater than current then swap
					{
						int temp=array[j];
						array[j]=array[j+1];
						array[j+1]=temp;
					}
			for(int i=0;i<n;i++) //Printing the sorted array
				printf("%d ",array[i]);
			printf("\nChild ends\n");
		}
		else //for the parent process...
			{
				printf("Parent is waiting for child to complete...\n");
        		wait(0); //parent waits for child to finish
        		printf("The Descending Sort of Array here by Parent:\n"); //Sorting array into descending order using Bubble Sort
				for(int i=0;i<n;i++)
					for(int j=0;j<n-i-1;j++)
						if(array[j]<array[j+1]) //if the next element is smaller than current then swap
						{
							int temp=array[j];
							array[j]=array[j+1];
							array[j+1]=temp;
						}
				for(int i=0;i<n;i++) //Printing the sorted array
					printf("%d ",array[i]);
				printf("\nParent ends\n");
			}
	return 0;
}