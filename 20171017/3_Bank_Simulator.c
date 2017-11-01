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
#define Num_Counters 3 //Number of counters

double Bank_Asset = 0;
float Balance[MAX_ACCOUNTS] = {0};
int Lim_Customers;

sem_t counter[Num_Counters], mutex[MAX_ACCOUNTS];

struct txn_det
{
	int Customer_No, Account_Num, Counter_Assigned;
	unsigned long Token_Number;
	float Txn_Amt;
};

void Debit(struct txn_det T)
{
	sem_wait(&counter[T.Counter_Assigned]);
	printf(KYEL "Customer : %d (TN = %lu) on counter %d, requesting Withdrawal of $ %0.2f on ACC : %d" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Txn_Amt, T.Account_Num + 1);
	
	sem_wait(&mutex[T.Account_Num]);
	printf(KGRN "Customer : %d (TN = %lu) on counter %d, got hold of ACC : %d" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Account_Num + 1);
	
	if(Balance[T.Account_Num] >= T.Txn_Amt)
	{
		Balance[T.Account_Num] -= T.Txn_Amt;
		Bank_Asset -= T.Txn_Amt;
		printf(KBLU "Customer : %d (TN = %lu) on counter %d, successfully Withdrew $ %0.2f (Current Balance[%d] = $ %0.2f)" KWHT "\tTotal Bank Asset = %lf" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Txn_Amt, T.Account_Num + 1, Balance[T.Account_Num], Bank_Asset);
	}
	else
		printf(KRED "Customer : %d (TN = %lu) on counter %d, unsuccessful in withdrawing because (Current Balance[%d] = $ %0.2f) < (Withdrawal Amt = $ %0.2f)" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Account_Num + 1, Balance[T.Account_Num], T.Txn_Amt);
	
	sem_post(&mutex[T.Account_Num]);
	sem_post(&counter[T.Counter_Assigned]);
	printf(KPRP "Customer : %d (TN = %lu) left the counter %d ..." KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned);
}

void Credit(struct txn_det T)
{
	sem_wait(&counter[T.Counter_Assigned]);
	printf(KYEL "Customer : %d (TN = %lu) on counter %d, requesting Deposit of $ %0.2f on ACC : %d" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Txn_Amt, T.Account_Num + 1);
	
	sem_wait(&mutex[T.Account_Num]);
	printf(KGRN "Customer : %d (TN = %lu) on counter %d, got hold of ACC : %d" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Account_Num + 1);
	
		Balance[T.Account_Num] += T.Txn_Amt;
		Bank_Asset += T.Txn_Amt;
		printf(KBLU "Customer : %d (TN = %lu) on counter %d, successfully Deposited $ %0.2f (Current Balance[%d] = $ %0.2f)" KWHT "\tTotal Bank Asset = %lf" KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned, T.Txn_Amt, T.Account_Num + 1, Balance[T.Account_Num], Bank_Asset);
	
	sem_post(&mutex[T.Account_Num]);
	sem_post(&counter[T.Counter_Assigned]);
	printf(KPRP "Customer : %d (TN = %lu) left the counter %d ..." KNRM "\n", T.Customer_No, T.Token_Number, T.Counter_Assigned);
}

void *Transaction(void *arg)
{
	struct txn_det T;
	T.Customer_No = *(int *)(arg);
	T.Token_Number = (unsigned long) pthread_self();
	T.Counter_Assigned = rand() % Num_Counters;
	T.Account_Num = rand() % MAX_ACCOUNTS;
	T.Txn_Amt = (float)(rand() % (TXN_LIM * 100)) / 100;
	switch(rand() % 2)
	{
		case 0:	Debit(T);
				break;
		case 1:	Credit(T);
				break;
	}
	pthread_exit(0);
}

int main()
{
	int i;
	
	for (i = 0; i < Num_Counters; i++)
		sem_init(&counter[i], 0, 1);
	for (i = 0; i < MAX_ACCOUNTS; i++)
		sem_init(&mutex[i], 0, 1);
	srand(time(NULL));
	for(i = 0; i < MAX_ACCOUNTS; i++)
	{
		Balance[i] = (float)(rand() % (TXN_LIM * 1000)) / 100;
		Bank_Asset += Balance[i];
	}
	printf(KWHT "Total Bank Asset : $ %0.2lf" KNRM "\n", Bank_Asset);
	printf("Enter the Limit of Customers : ");
	scanf("%d", &Lim_Customers);

	int Customers[Lim_Customers];
	pthread_t Transact[Lim_Customers];
	for (i = 0; i < Lim_Customers; i++)
	{
		Customers[i] = i+1;
		printf(KCYN "Customer %d entered the Bank ..." KNRM "\n", i+1);
		pthread_create(&Transact[i], NULL, Transaction, &Customers[i]);
	}

	for(i = 0; i < Lim_Customers; i++)
		pthread_join(Transact[i], NULL);

	return 0;
}