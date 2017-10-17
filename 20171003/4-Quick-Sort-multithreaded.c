/* program for Quick Sort using pthread */
/* compile with the "-pthread" option*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 50 /* Maximum Size for array */
#define MSORT_FALSE size > MAX_SIZE /* Condition for Sort not possible in this program */

int A[MAX_SIZE]; // Declaration of Array to be used by all threads
int size; // size for the current array to be input by user
int pivot; // pivot variable for saving pivot from each thread

struct Partition_details /* structure for the details for Partition */
{
	int left, right;
};

void swap(int *a,int *b) //function definition to swap two integers
{
	int t=*a; //temporary variable
	*a=*b;
	*b=t;
}

void *Partition(void *arg) // runner funtion for Partitioning threads
{
	printf("\tPartition called ... thread : %lu\n", pthread_self());
	struct Partition_details *detail = arg; // arg will give the details for the array to be Partitioned

	int i = detail->left - 1; //Index of smaller element which will become the pivot index later
	for(int j = detail->left; j <= detail->right - 1; j++) //from left to the right of array
		if(A[j] <= A[detail->right]) //if current element is smaller than pivot element (rightmost element)
			swap(&A[++i], &A[j]); //swap the next i-th element with current j-th
	swap(&A[++i], &A[detail->right]); // after loop ends swap the next i-th element and the rightmost element
	pivot = i; // changing the pivot

	printf("\tPartition ... thread : %lu finished\n", pthread_self());
	pthread_exit; // exiting the thread
}

void *QuickSort(void *arg) // runner function for sorting threads
{
	printf("QuickSort called ... thread : %lu\n", pthread_self());
	struct Partition_details *detail = arg; // arg will give details for the left and right of array to be sorted

	if(detail->left < detail->right) // if the left index is smaller than right
	{
		pthread_t tid_l, tid_r, tid_p;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid_p, &attr, Partition, detail);
		pthread_join(tid_p, NULL);

		struct Partition_details *Left = malloc(sizeof(struct Partition_details));
		Left->left = detail->left;
		Left->right = pivot - 1;
		struct Partition_details *Right = malloc(sizeof(struct Partition_details));
		Right->left = pivot + 1;
		Right->right = detail->right;
		pthread_create(&tid_l, &attr, QuickSort, Left);
		pthread_create(&tid_r, &attr, QuickSort, Right);
		pthread_join(tid_l, NULL);
		pthread_join(tid_r, NULL);
	}

	printf("QuickSort ... thread : %lu finished\n", pthread_self());
	pthread_exit; // exiting the thread
}

int main() /* main module */
{
	/* getting the array size */
	printf("Enter the size of the array (<= %d): ", MAX_SIZE);
	scanf("%d", &size);

	if (MSORT_FALSE) /* if size is beyond limit close program */
	{
		printf("You entered a larger size than %d... go to the source code and modify limit\n", MAX_SIZE);
		return 0; // return from main module
	}

	/* getting array data */
	printf("Enter the array data\n");
	for(int i = 0; i < size; i++)
		scanf("%d", A + i);

	/* declaring thread for the task */
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* initializing the thread for Quick sort */
	struct Partition_details *S = malloc(sizeof(struct Partition_details));
	S->left = 0;
	S->right = size-1;
	pthread_create(&tid, &attr, QuickSort, S);
	pthread_join(tid, NULL); // waiting for the Quicksort thread to finish

	/* printing the array */
	for(int i = 0; i < size;  i++)
		printf("%d\t", A[i]);
	printf("\n");

	return 0; // return from main module
}