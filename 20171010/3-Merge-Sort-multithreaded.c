/* program for Merge Sort using pthread */
/* compile with the "-pthread" option*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int A[] = {0, 2, 1, 5, 10, 8, 9, 15, 12, 10, 9, 15}; // Declaration of Array to be used by all threads
int size = sizeof(A)/sizeof(A[0]); // size for the current array to be input by user

struct merge_details /* structure for the details for merge operation */
{
	int left, middle, right;
};

struct sort_details /* structure for the details for sort operation */
{
	int left, right;
};

void *merge(void *arg) // runner funtion for merger threads
{
	/*printf("\tMerge called ... thread : %lu\n", pthread_self());*/
	struct merge_details *detail = arg; // arg will give the details for the array to be merged
	int i, j, k;
	int n1 = detail->middle - detail->left + 1; // length of left sub array
	int n2 = detail->right - detail->middle; // length of right sub array
	int L[n1], R[n2]; // Left and Right temporary arrays

	for(i = 0; i < n1; i++) // copying the Left array part into L[]
		L[i] = A[detail->left + i];
	for(j = 0; j < n2; j++) // copying the Right array part into R[]
		R[j] = A[detail->middle + 1 + j];

	// Merging the temporary arrays back into A[l..r]
	i = 0; j = 0; k = detail->left; // Initial index of Left,Right,merged subarray
	while(i < n1 && j < n2) // till Left or Right array's end is reached...
	{
		if(L[i] <= R[j]) // if current element of Left array is smaller or equal to the current of Right array...
			A[k++] = L[i++]; // store the current Left array element into current element of A[] and then increment i and k
		else // else...
			A[k++] = R[j++]; // store the current Right array element into current element of A[] and then increment j and k
	}

	while(i < n1) // if there are any elements left from Left array...
		A[k++] = L[i++]; // copy each of them into the A[]
	while (j < n2) // if there are any elements left from Right array...
		A[k++] = R[j++]; // copy each of them into the A[]

	/*printf("\tMerge thread : %lu finished\n", pthread_self());*/
	pthread_exit; // exiting the thread
}

void *mergeSort(void *arg) // runner function for sorting threads
{
	struct sort_details *detail = arg; // arg will give details for the left and right of array to be sorted

	if(detail->left < detail->right) // if the left index is smaller than right
	{
		int m = detail->left + (detail->right - detail->left)/2; // same as (l+r)/2 but avoids overflow for larger l and r
		/*printf("MergeSort called ... thread : %lu\n", pthread_self());*/

		struct sort_details *Left = malloc(sizeof(struct sort_details)); // structure variable to store detail for sorting left array
		Left->left = detail->left;
		Left->right = m;
		struct sort_details *Right = malloc(sizeof(struct sort_details)); // structure variable to store detail for sorting right array
		Right->left = m+1;
		Right->right = detail->right;

		pthread_t tid_l, tid_r, tid_m; // threads for sorting left array, right array and then merging them
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid_l, &attr, mergeSort, Left); // thread to sort left array
		pthread_create(&tid_r, &attr, mergeSort, Right); // thread to sort right array
		pthread_join(tid_l, NULL); // waiting for left sort thread
		pthread_join(tid_r, NULL); // waiting for right sort thread

		struct merge_details *MRG = malloc(sizeof(struct merge_details)); // structure variable to store details for merging
		MRG->left = detail->left;
		MRG->middle = m;
		MRG->right = detail->right;
		pthread_create(&tid_m, &attr, merge, MRG); // thread to merge both arrays
		pthread_join(tid_m, NULL); // waiting for the merger thread
	}

	/*printf("MergeSort ... thread : %lu finished\n", pthread_self());*/
	pthread_exit; // exiting the thread
}

int main() /* main module */
{
	/* printing array data */
	printf("Array Data for Merge Sort : \n");
	for(int i = 0; i < size; i++)
		printf("%6d ", *(A + i));
	printf("\n");

	/* declaring thread for the task */
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* initializing the thread for merge sort */
	struct sort_details *S = malloc(sizeof(struct sort_details));
	S->left = 0;
	S->right = size-1;
	pthread_create(&tid, &attr, mergeSort, S);
	pthread_join(tid, NULL); // waiting for the mergesort thread to finish

	/* printing the sorted array */
	printf("\nSorted Array Data (Merge Sort) : \n");
	for(int i = 0; i < size;  i++)
		printf("%6d ", A[i]);
	printf("\n");

	return 0; // return from main module
}