/* program for matrix multiplication using pthread */
/* compile with the "-pthread" option*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ROW 20 /* Maximum Row Size */
#define MAX_COL 20 /* Maximum Column Size */
#define MATMUL_FALSE ROW1 > MAX_ROW || ROW2 > MAX_ROW || COL1 > MAX_COL || COL2 > MAX_COL || COL1 != ROW2 /* case for matrix multiplication not possible */

int A[MAX_ROW][MAX_COL] = 
{{1, 1},
{1, 2},
{2, 3},
{8, 1}}; /* declaring and initializing Matrix A */
int B[MAX_ROW][MAX_COL] = 
{{1, 1, 1, 2},
{2, 3, 8, 1}}; /* declaring and initializing Matrix B */
int C[MAX_ROW][MAX_COL]; /* Declaring Matrix C */
int ROW1 = 4, COL1 = 2, ROW2 = 2, COL2 = 4; /* Row & Column variables for both matrices */

struct co_ord /* structure for the coordinate of an element */
{
	int row; /* row number */
	int col; /* column number */
};

void *MulMatRunner(void *param) /* The thread runner code to calculate corresponding Multiplied element */
{
	struct co_ord *COORD = param; /* parameter will give the COORDINATE for the current element to calculate */
	
	/* calculating the respective element of resultant matrix */
	int sum = 0;
	for(int i = 0; i < COL1; i++)
		sum += A[COORD -> row][i] * B[i][COORD -> col];
	C[COORD -> row][COORD -> col] = sum;
	
	/* exiting the thread */
	pthread_exit;
}

int main() /* main module */
{
	if(MATMUL_FALSE) /* if the matrices can't be mutliplied */
	{
		printf("Matrix multiplication either not possible or size out of range\n");
		return 0; /* return from main module */
	}

	/*  printing data for both the matrices A & B */
	printf("Matrix A for multiplication: \n");
	for(int i = 0; i < ROW1; i++)
	{
		printf(" |");
		for(int j = 0; j < COL1; j++)
			printf("%6d ", A[i][j]);
		printf("|\n");
	}
	printf("Matrix B for multiplication: \n");
	for(int i = 0; i < ROW2; i++)
	{
		printf(" |");
		for(int j = 0; j < COL2; j++)
			printf("%6d ", B[i][j]);
		printf("|\n");
	}

	/* declaring threads for the task */
	pthread_t tid[ROW1][COL2];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* initializing threads for matrix multiplication */
	for(int i = 0; i < ROW1; i++)
		for(int j = 0; j < COL2; j++)
		{
			struct co_ord *THIS = malloc(sizeof(struct co_ord));
			THIS -> row = i;
			THIS -> col = j;
			pthread_create(&tid[i][j],&attr,MulMatRunner,THIS);
		}

	/* waiting for all threads to finish */
	for(int i = 0; i < ROW1; i++)
		for(int j = 0; j < COL2; j++)
			pthread_join(tid[i][j],NULL);

	/* printing the multiplied resultant matrix C */
	printf("Resultant Matrix C (product): \n");
	for(int i = 0; i < ROW1; i++)
	{
		printf(" |");
		for(int j = 0; j < COL2; j++)
			printf("%6d  ", C[i][j]);
		printf("|\n");
	}

	printf("\n");
	return 0; /* return from main module */
}