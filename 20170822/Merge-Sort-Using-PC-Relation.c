/*	C program for Merge Sort 
    using Parent Child Relationship for
    divide and conquer strategy here
    using vfork*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void merge(int arr[],int l,int m,int r) //Function definition for merging two subarrays of arr[]: arr[l...m] and arr[m+1...r] with sorting in ascending order
{
	int i,j,k;
	int n1=m-l+1; //length of left sub array
	int n2=r-m; //length of right sub array
	int L[n1],R[n2]; //Left and Right temporary arrays

	for(i=0;i<n1;i++) //copying the Left array part into L[]
		L[i]=arr[l+i];
	for(j=0;j<n2;j++) //copying the Right array part into R[]
		R[j]=arr[m+1+j];

	// Merging the temporary arrays back into arr[l..r]
	i=0; j=0; k=l; // Initial index of Left,Right,merged subarray
	while(i<n1&&j<n2) //till Left or Right array's end is reached...
	{
		if(L[i]<=R[j]) //if current element of Left array is smaller or equal to the current of Right array...
			arr[k++]=L[i++]; //store the current Left array element into current element of arr[] and then increment i and k
		else //else...
			arr[k++]=R[j++]; //store the current Right array element into current element of arr[] and then increment j and k
	}

	while(i<n1) //if there are any elements left from Left array...
		arr[k++]=L[i++]; //copy each of them into the arr[]
	while (j < n2) //if there are any elements left from Right array...
		arr[k++]=R[j++]; //copy each of them into the arr[]
}

void mergeSort(int arr[], int l, int r) //function definition to divide the array into to halves and merge recursively with sorting
{
	if(l<r) //if the left index is smaller than right
	{
		int m=l+(r-l)/2; //same as (l+r)/2 but avoids overflow for larger l and r
		pid_t pid;
		int status;
		if((pid=vfork())<0) //vfork a child process & if failed...
		{
			printf("\t\t\t ERROR: forking child process failed \n"); //failed fork message
			exit(1); //exit out that process
		}
		else //else if successful...
			if(pid==0) //for the child process...
			{
				mergeSort(arr,l,m); //sort the left half
				mergeSort(arr,m+1,r); //sort the right half
				exit(1);
			}
			else //and for the parent process...
			{
				while(wait(&status)!=pid); //wait for completion
				merge(arr,l,m,r); //merge these two halves
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

	mergeSort(arr,0,arr_size-1); //calling the mergesort function

	printf("\nSorted array is \n"); //printing the sorted array
	printArray(arr,arr_size);
	return 0;
}
