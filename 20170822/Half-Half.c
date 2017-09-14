// Half half Ascending and descending sort in Parent Child Setup
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int n;
	printf("Enter the size of array 'n': ");
	scanf("%d",&n);
	int array[n];
	printf("Enter the array data \n");
	for(int i=0;i<n;i++)
		scanf("%d",&array[i]);
	int tempn=n/2;
	pid_t pid=fork();
	if(pid<0)
		printf("Fork Failed\n");
	else
		if(pid==0)
		{
			printf("The Descending Sort on Second Half of Array here by Child:\n");
			for(int i=tempn;i<n;i++)
				for(int j=tempn;j<n-i+tempn-1;j++)
					if(array[j]<array[j+1])
					{
						int temp=array[j];
						array[j]=array[j+1];
						array[j+1]=temp;
					}
			for(int i=0;i<n;i++)
				if(i==tempn)
					printf("++ %d ",array[i]);
				else
					printf("%d ",array[i]);
			printf("\nChild ends\n");
		}
		else
			{
				printf("Parent is waiting for child to complete...\n");
        		wait(0);
        		printf("The Ascending Sort on First Half of Array here by Parent:\n");
				for(int i=0;i<tempn;i++)
					for(int j=0;j<tempn-i-1;j++)
						if(array[j]>array[j+1])
						{
							int temp=array[j];
							array[j]=array[j+1];
							array[j+1]=temp;
						}
				for(int i=0;i<n;i++)
				if(i==tempn)
					printf("++ %d ",array[i]);
				else
					printf("%d ",array[i]);
				printf("\nParent ends\n");
			}
	return 0;
}