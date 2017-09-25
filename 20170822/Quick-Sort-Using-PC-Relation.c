/*	C program for Quick Sort 
    using Parent Child Relationship for
    divide and conquer strategy here
    using vfork*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void swap(int *a,int *b) //function definition to swap two integers
{
	int t=*a; //temporary variable
	*a=*b;
	*b=t;
}

int Partition(int arr[],int left,int right) //function definition to find the pivot
{
	int i=(left-1); //Index of smaller element which will become the pivot index later
	for(int j=left;j<=right-1;j++) //from left to the right of array
		if(arr[j]<=arr[right]) //if current element is smaller than pivot element (rightmost element)
			swap(&arr[++i],&arr[j]); //swap the next i-th element with current j-th
	swap(&arr[++i],&arr[right]); //after loop ends swap the next i-th element and the rightmost element
	return (i); //return th epivot index
}

void QuickSort(int arr[],int left,int right) //function definition to Quick Sort
{
	if(left<right) //if the left index is smaller than the right
	{
		pid_t pid;
		int status,pivot;
		if((pid=vfork())<0) //vfork a child process & if failed...
		{
			printf("\t\t\t ERROR: forking child process failed \n"); //failed fork message
			exit(1); //exit out that process
		}
		else //else if successful...
			if(pid==0) //for the child process...
			{
				pivot=Partition(arr,left,right); //getting pivot index by partition function
				exit(1);
			}
			else //and for the parent process...
			{
				while(wait(&status)!=pid); //wait for completion
				QuickSort(arr,left,pivot-1); //QuickSort the array left to the pivot
				QuickSort(arr,pivot+1,right); //QuickSort the array right to the pivot
			}
	}
}

void printArray(int A[],int size) //function definition to print an array
{
	for(int i=0;i<size;i++) //until the end of array is reached...
		printf("%d ",A[i]); //print each element
	printf("\n"); //move cursor to next line after printing the entire array
}

int main() // main module
{
	int arr_size; //getting the array size from the user
	printf("Enter the size of the Array: ");
	scanf("%d",&arr_size);

	int arr[arr_size]; //gettin the array data from the user
	printf("Enter the data in the Array: ");
	for(int i=0;i<arr_size;i++)
		scanf("%d",&arr[i]);	

    printf("Given array before sorting \n"); //printing the entered unsorted array
    printArray(arr,arr_size);

	QuickSort(arr,0,arr_size-1); //calling the quick sort function

	printf("\nSorted array is \n"); //printing the sorted array
	printArray(arr,arr_size);
	return 0;
}