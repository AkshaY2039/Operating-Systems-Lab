/* program for matrix multiplication using pthread */
/* compile with the "-pthread" option*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ROW 20 /* Maximum Row Size */
#define MAX_COL 20 /* Maximum Column Size */
#define MATMUL_FALSE ROW1 > MAX_ROW || ROW2 > MAX_ROW || COL1 > MAX_COL || COL2 > MAX_COL || COL1 != ROW2 /* case for matrix multiplication not possible */

int A[MAX_ROW][MAX_COL] = {{0}}; /* declaring and initializing Matrix A */
int B[MAX_ROW][MAX_COL] = {{0}}; /* declaring and initializing Matrix B */
int C[MAX_ROW][MAX_COL]; /* Declaring Matrix C */
int ROW1, COL1, ROW2, COL2; /* Row & Column variables for both matrices */

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
	/* getting the size for matrix A */
	printf("Enter the Row and Column size for Matrix A:\n");
	printf("Row Size (<= %d) : ", MAX_ROW);
	scanf("%d", &ROW1);
	printf("Column Size (<= %d) : ", MAX_COL);
	scanf("%d", &COL1);

	/* getting the size for matrix B */
	printf("Enter the Row and Column size for Matrix B:\n");
	printf("Row Size (<= %d) : ", MAX_ROW);
	scanf("%d", &ROW2);
	printf("Column Size (<= %d) : ", MAX_COL);
	scanf("%d", &COL2);

	if(MATMUL_FALSE) /* if the matrices can't be mutliplied */
	{
		printf("Matrix multiplication either not possible or size out of range\n");
		return 0; /* return from main module */
	}

	/*  getting data for both the matrices A & B */
	printf("Enter the data for Matrix A: \n");
	for(int i = 0; i < ROW1; i++)
		for(int j = 0; j < COL1; j++)
			scanf("%d", &A[i][j]);
	printf("Enter the data for Matrix B: \n");
	for(int i = 0; i < ROW2; i++)
		for(int j = 0; j < COL2; j++)
			scanf("%d", &B[i][j]);

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
	printf("Resultant Matrix C: \n");
	for(int i = 0; i < ROW1; i++)
	{
		for(int j = 0; j < COL2; j++)
			printf("%d  ", C[i][j]);
		printf("\n");
	}

	return 0; /* return from main module */
}