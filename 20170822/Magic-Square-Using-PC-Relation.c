/*Magic Square Generation in Parent Child Relationship
 (generation in one process and checking in another)*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int size_o_matrix;
	printf("Enter the size of matrix : ");
	scanf("%d", &size_o_matrix);

	if(size_o_matrix % 2 == 0)
		printf("Magic Square exist only for Odd Sized matrix\n");
	else
	{
		int matrix[size_o_matrix][size_o_matrix];
		pid_t pid = vfork();
		if(pid < 0)
		{
			printf("Fork Failed...\n");
			exit(0);
		}
		else
			if(pid == 0)
			{
				printf("Now child is generating the Magic Square\n");
				int i = size_o_matrix/2;
				int j = size_o_matrix-1;
				// set all slots as 0
    			memset(matrix, 0, sizeof(matrix));
				for (int num=1; num <= size_o_matrix*size_o_matrix; )
				{
					if (i==-1 && j==size_o_matrix) //3rd condition
					{
						j = size_o_matrix-2;
						i = 0;
					}
					else
					{
						//1st condition helper if next number 
						// goes to out of square's right side
						if (j == size_o_matrix)
							j = 0;
						//1st condition helper if next number 
						// is goes to out of square's upper side
						if (i < 0)
							i=size_o_matrix-1;
					}
					if (matrix[i][j]) //2nd condition
					{
						j -= 2;
						i++;
						continue;
					}
					else
						matrix[i][j] = num++; //set number
			 
					j++; i--; //1st condition
				}
				for(int i = 0; i < size_o_matrix; i++)
				{
					for(int j = 0; j < size_o_matrix; j++)
						printf("%6d  ", matrix[i][j]);
					printf("\n");
				}
				exit(0);
			}
			else
			{
				printf("Parent Waiting for the child\n");
				wait(0);
				long diag_sum[2] = {0};
				long col_sum[size_o_matrix], row_sum[size_o_matrix];
				// set all slots as 0
    			memset(col_sum, 0, sizeof(col_sum));
    			memset(row_sum, 0, sizeof(row_sum));
				for(int i = 0; i < size_o_matrix; i++)
					for(int j = 0; j < size_o_matrix; j++)
					{
						if(i == j)
							diag_sum[1]+=matrix[i][j];
						if((i + j) == (size_o_matrix - 1))
							diag_sum[0]+=matrix[i][j];
						row_sum[i] = matrix[i][j];
						col_sum[j] = matrix[i][j];
					}
				int success = 1;
				long Magic_Const = size_o_matrix*(size_o_matrix*size_o_matrix+1)/2;
				for(int i = 0; i < 2; i++)
					if(diag_sum[i] != Magic_Const)
						success = 0;
				for(int i = 0; i < size_o_matrix; i++)
					if(col_sum[i] != Magic_Const || row_sum[i] != Magic_Const)
						success = 0;

				printf("Magic Constant = %li \n", Magic_Const);
				if(!success)
				{
					printf("Child generate the correct magic square\n");
				}
				else
				{
					printf("Child failed the task\n");
				}
			}
	}
	return 0;
}