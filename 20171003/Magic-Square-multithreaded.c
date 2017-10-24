/* program for magic square generation using pthread */
/* compile with the "-pthread" option*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define SIZE 5

int square[SIZE][SIZE];
int sum;

void *populate(void *p)
{
	int n = *(int*)p;
	int magic[n][n];

	memset(magic, 0, sizeof(magic));

	int i = n/2;
	int j = n-1;

	for(int num = 1; num <= n*n; )
	{
		if (i==-1 && j==n)
		{
			j = n-2;
			i = 0;
		}
		else
		{
			if(j == n)
				j = 0;
			if(i < 0)
				i=n-1;
		}
		if(magic[i][j])
		{
			j -= 2;
			i++;
			continue;
		}
		else
			magic[i][j] = num++;
		j++; i--;
	}

	printf("\nThe Magic Square for n = %d\nSum of each row or column : %d\n\n", n, n*(n*n+1)/2);
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%6d ", magic[i][j]);
			square[i][j] = magic[i][j];
		}
		printf("\n");
	}
	printf("\n");

	printf("Populating the Magic Square finished by tid : %lu...\n", pthread_self());
	pthread_exit(0);
}

void *Vertical_Checker(void *p)
{
	int index = *(int*)p;
	int i,check = 0;

	for(i = 0; i < SIZE; ++i)
		check += square[i][index];

	if(check == sum)
		printf("The Thread tid = %lu verified magic const for row : %d\n", pthread_self(), index);
	pthread_exit(0);
}

void *Horixontal_Checker(void *p)
{
	int index = *(int*)p;
	int i,check = 0;

	for(i = 0; i < SIZE; ++i)
		check += square[index][i];

	if (check == sum)
		printf("The Thread tid = %lu verified magic const for column : %d\n", pthread_self(), index);
	pthread_exit(0);
}

void *RDiagonal_Checker(void *p)
{
	int i,check = 0;

	for(i = 0; i < SIZE; ++i)
		check += square[i][i];

	if (check == sum)
		printf("The Thread tid = %lu verified magic const for right diagonal\n", pthread_self());
	pthread_exit(0);
}

void *LDiagonal_Checker(void *p)
{
	int i,check = 0;

	for(i = 0; i < SIZE; ++i)
		check += square[SIZE-i-1][i];

	if (check == sum)
		printf("The Thread tid = %lu verified magic const for left diagonal\n", pthread_self());
	pthread_exit(0);
}

int main()
{
	int n = SIZE; 
	if(n%2 == 0)
	{
		printf("\nMagic Square is valid only for an ODD size\n");
		return 0;
	}

	sum = n*(n*n+1)/2;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t make_square;

	pthread_create(&make_square, NULL, populate, &n);

	pthread_join(make_square, NULL);

	pthread_t Vertical_Check[n];
	pthread_t Horixontal_Check[n];
	pthread_t Diagonal_Check[2];

	int v[n], h[n];

	for (int i = 0; i < n ; ++i)
	{
		v[i] = i;
		pthread_create(&Vertical_Check[i], &attr, Vertical_Checker, &v[i]);
	}
	for (int i = 0; i < n; ++i)
	{
		h[i] = i;
		pthread_create(&Horixontal_Check[i], &attr, Horixontal_Checker, &h[i]);
	}
	pthread_create(&Diagonal_Check[0], &attr, RDiagonal_Checker, NULL);
	pthread_create(&Diagonal_Check[1], &attr, LDiagonal_Checker, NULL);

	for (int i = 0; i < n; ++i)
		pthread_join(Vertical_Check[i], NULL);
	for (int i = 0; i < n; ++i)
		pthread_join(Horixontal_Check[i], NULL);
	pthread_join(Diagonal_Check[0], NULL);
	pthread_join(Diagonal_Check[1], NULL);
	return 0;
}