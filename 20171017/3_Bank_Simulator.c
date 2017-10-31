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

#define MAX_ACCOUNTS 10 //limit for the maximum number of existing Accounts
#define TXN_LIM 5000 //Limit for one transaction

float Bank_Asset = 0;
float Balance[MAX_ACCOUNTS] = {0};

sem_t counter[3], customers;

struct txn_det
{
	int Account_Num;
	int Token_Number;
	int Counter_Assigned;
};

void *Transaction(void *arg)
{
	
}

int main()
{
	for(int i = 0; i < MAX_ACCOUNTS; i++)
	{
		Balance[i] = (float)(rand()) % TXN_LIM / 100;
		Bank_Asset += Balance[i];
	}
	printf("Total Bank : $%f\n", Bank_Asset);
	return 0;
}