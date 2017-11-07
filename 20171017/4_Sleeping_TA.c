#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> /* for sleep */

#define KNRM  "\033[0m"	//RESET COLOR
#define KRED  "\033[1;31m" //RED COLOR
#define KGRN  "\033[1;32m" //GREEN COLOR
#define KYEL  "\033[1;33m" //YELLOW COLOR
#define KBLU  "\033[1;34m" //BLUE COLOR
#define KPRP  "\033[1;35m" //PURPLE COLOR
#define KCYN  "\033[1;36m" //CYAN COLOR
#define KWHT  "\033[1;37m" //WHITE COLOR

int Number_of_chairs, TAMODE = 0;
int Number_of_students, CHAIR;

sem_t chairs, TA;

void check_TA()
{
	if(TAMODE == 0)
		printf(KGRN "The TA is sleeping now ... " KNRM "\n");
}

void WakeUpTA(int student_id)
{
	srand(time(NULL));
	sleep(rand()%10);

	sem_wait(&chairs);
	printf(KRED "Student %d is waiting on the chair ..." KNRM "\n", student_id);
	sem_wait(&TA);

	sem_post(&chairs);
	TAMODE = 1;
	printf(KCYN "The TA woke up for student : %d and has started teaching ..." KNRM "\n", student_id);
	srand(time(NULL));
	sleep(rand()%5);
	
	printf(KYEL "Student %d has left ..." KNRM "\n", student_id);
	
	sem_getvalue(&chairs, &CHAIR);
	if(CHAIR == Number_of_chairs)
		TAMODE = 0;
	
	sem_post(&TA);
}

void *Student(void *Arg)
{
	int *student_id = Arg;
	WakeUpTA(*student_id);
	check_TA();
	pthread_exit(0);
}

int main()
{
	sem_init(&TA, 0, 1);
	printf("Enter the MAX_LIMIT for chairs in the queue : ");
	scanf("%d", &Number_of_chairs);
	sem_init(&chairs, 0, Number_of_chairs);
	printf("Enter the Number of Students in class : ");
	scanf("%d", &Number_of_students);
	pthread_t Students[Number_of_students];

	int i, ST_ID[Number_of_students];
	check_TA();
	for(i = 0; i < Number_of_students; i++)
	{
		ST_ID[i] = i + 1;
		pthread_create(&Students[i], NULL, Student, &ST_ID[i]);
	}

	for(i = 0; i < Number_of_students; i++)
		pthread_join(Students[i], NULL);

	return 0;
}