/* program for matrix inverse using pthread */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ORDER 20 /* maximum order of the matrix */

long Det; /* Variable to store Determinant */
int Order; /* Order of the Matrix */
int Mat[MAX_ORDER][MAX_ORDER] = {{0}}, AltMat[MAX_ORDER][MAX_ORDER] = {{0}};

struct MatData
{
	int row; /* row number */
	int col; /* column number */
	int size; /* size of matrix */
};

/* Calculating Co Factor of A[r][c] in temp[][] where size is current order of A[][] */
void CalCoFac(int A[MAX_ORDER][MAX_ORDER], int temp[MAX_ORDER][MAX_ORDER], int r, int c, int size)
{
	int row = 0, col = 0;

	/* for each element of matrix A*/
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			// Copying into temporary matrix only those element
			// which are not in given row and column
			if (i != p && j != q)
			{
				temp[row][col++] = A[i][j];

				// Row is filled, so increase row index and
				// reset col index
				if (col == size - 1)
				{
					col = 0;
					row++;
				}
			}
}
