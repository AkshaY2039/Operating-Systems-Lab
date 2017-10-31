#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> /* for sleep */

#define KNRM  "\033[0m"	//RESET COLOR
#define KYEL  "\033[1;33m" //YELLOW COLOR
#define KRED  "\033[1;31m" //RED COLOR
#define KGRN  "\033[1;32m" //GREEN COLOR

int MAX_LIMIT;
int Number_o_Users;
//time_t t;

sem_t license, mutex;

/*void Random_Use_Time(int minimum, int maximum)
{
	srand ((unsigned) time(&t));
	int range = maximum - minimum;
	sleep(minimum + rand() % range);
}*/

void Request_License(int UNum)
{
	sem_wait(&mutex);
	printf(KYEL "User %d is requesting the license..." KNRM "\n", UNum);
	sem_wait(&license);
	printf(KGRN "User %d has got hold of the license..." KNRM "\n", UNum);
	sem_post(&mutex);
}

void Release_License(int UNum)
{
	printf(KRED "User %d is releasing the license..." KNRM "\n", UNum);
	sem_post(&license);
}

void *User_Online(void *arg)
{
	int *UNum = arg;
	char req[15];
	while(1)
	{
		Request_License(*UNum);
		sprintf(req, "./colors.out %d", *UNum);
		system(req);
		sleep(1);
		//Random_Use_Time(0,5);
		Release_License(*UNum);
	}
}

int main()
{
	sem_init(&mutex, 0, 1);
	printf("Enter the MAX_LIMIT for users simultaneously using the license : ");
	scanf("%d", &MAX_LIMIT);
	sem_init(&license, 0, MAX_LIMIT);
	printf("Enter the Number of Users to simulate for : ");
	scanf("%d", &Number_o_Users);
	pthread_t User[Number_o_Users];

	int i, UNO[Number_o_Users];
	for(i = 0; i < Number_o_Users; i++)
	{
		UNO[i] = i + 1;
		printf("User %d is Online\n", UNO[i]);
		pthread_create(&User[i], NULL, User_Online, &UNO[i]);
	}

	for(i = 0; i < Number_o_Users; i++)
		pthread_join(User[i], NULL);

	return 0;
}