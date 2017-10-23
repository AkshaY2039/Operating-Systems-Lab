/* using SCHED policies to schedule binaries */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define KNRM  "\033[0m" //RESET COLOR
#define KRED  "\033[1;31m" //RED COLOR
#define KGRN  "\033[1;32m" //GREEN COLOR

void* Inverse ()
{
	printf(KGRN "Matrix Inverse Started ... Mapped to thread : %lu" KNRM "\n", pthread_self());
	system("./Inverse");
	printf(KRED "Matrix Inverse thread : %lu finished" KNRM "\n", pthread_self());
	pthread_exit(0);
}

void* MergeSort ()
{
	printf(KGRN "Merge Sort Started ... Mapped to thread : %lu" KNRM "\n", pthread_self());
	system("./MergeSort");
	printf(KRED "Merge Sort thread : %lu finished" KNRM "\n", pthread_self());
	pthread_exit(0);
}

void* MatMul ()
{
	printf(KGRN "Matrix Multiplication Started ... Mapped to thread : %lu" KNRM "\n", pthread_self());
	system("./MatMul");
	printf(KRED "Matrix Multiplication thread : %lu finished" KNRM "\n", pthread_self());
	pthread_exit(0);
}

void* MagicSq ()
{
	printf(KGRN "Magic Square Started ... Mapped to thread : %lu" KNRM "\n", pthread_self());
	system("./MagicSq");
	printf(KRED "Magic Square thread : %lu finished" KNRM "\n", pthread_self());
	pthread_exit(0);
}

void* QuickSort ()
{
	printf(KGRN "Quick Sort Started ... Mapped to thread : %lu" KNRM "\n", pthread_self());
	system("./QuickSort");
	printf(KRED "Quick Sort thread : %lu finished" KNRM "\n", pthread_self());
	pthread_exit(0);
}

int main()
{
	int choice;
	printf("Select a sched policy: 1) RR 2) FIFO 3)OTHER: ");
	scanf("%d", &choice);

	pthread_t tid[5];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// set schedule policy
	switch(choice)
	{
		case 1:
			printf("Set schedule policy RR\n");
			pthread_attr_setschedpolicy(&attr, SCHED_RR);
			break;
		case 2:
			printf("Set schedule policy FIFO\n");
			pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
			break;
		case 3:
			printf("Set schedule policy OTHER\n");
			pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
			break;
	}

	pthread_create(&tid[0], &attr, &QuickSort, NULL);
	pthread_create(&tid[1], &attr, &MatMul, NULL);
	pthread_create(&tid[2], &attr, &Inverse, NULL);
	pthread_create(&tid[3], &attr, &MagicSq, NULL);
	pthread_create(&tid[4], &attr, &MergeSort, NULL);

	// join
	for( int i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);

	return 0;
}