/* using SCHED policies to schedule binaries */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* Inverse ()
{
	system("./Inverse");
	pthread_exit(0);
}

void* MergeSort ()
{
	system("./MergeSort");
	pthread_exit(0);
}

void* MatMul ()
{
	system("./MatMul");
	pthread_exit(0);
}

void* MagicSq ()
{
	system("./MagicSq");
	pthread_exit(0);
}

void* QuickSort ()
{
	system("./QuickSort");
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
	pthread_create(&tid[4], &attr, &QuickSort, NULL);

	// join
	for( int i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);

	return 0;
}