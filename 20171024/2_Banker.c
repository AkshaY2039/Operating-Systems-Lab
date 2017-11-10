#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROC_NUM 10
#define MAX_RES_TYPE 10

int Number_o_Processes;
int Number_o_Res_Types;

int claim[MAX_PROC_NUM][MAX_RES_TYPE];
int alloc[MAX_PROC_NUM][MAX_RES_TYPE];
int need[MAX_PROC_NUM][MAX_RES_TYPE];

int resource_count[MAX_RES_TYPE];
int available[MAX_RES_TYPE];
int finished[MAX_PROC_NUM] = {0};

int find_available()
{
	int used[MAX_RES_TYPE] = {0};
	for(int i = 0; i<Number_o_Res_Types; i++)
	{
		for(int j = 0; j<Number_o_Processes; j++)
			used[i] = used[i] + alloc[j][i];

		available[i] = resource_count[i] -  used[i];
		if(available[i]<0)
			return 0;
	}
	return 1;
}

int find_need()
{
	for(int i = 0; i<Number_o_Processes; i++)
		for(int j = 0; j<Number_o_Res_Types; j++)
		{
			need[i][j] = claim[i][j] - alloc[i][j];
			if(need[i][j] < 0)
				return -1 ;
		}
	return 1;
}

int find_row()
{
	int st = 1, j, i;
	for(i = 0; i<Number_o_Processes; i++)
	{
		if(finished[i])
			continue;
		for(j = 0; j<Number_o_Res_Types; j++)
			if(need[i][j] > available[j])
			{
				st = 0;
				break;
			}
		if(j == Number_o_Res_Types)
				return i;
	}
	return -1;
}

int banker()
{
	printf("Safe Sequence for execution is as follows\n");
	int is_finished = 0;
	while(!is_finished)
	{
		find_need();
		int row = find_row();
		if(row == -1)
			return 0;
		printf("P %d \t", row);

		for(int i = 0; i<Number_o_Res_Types; i++)
		{
			available[i] = available[i] + alloc[row][i];
			alloc[row][i] = 0;
			finished[row ] = 1;
		}
		is_finished = 1;
		for(int i = 0; i<Number_o_Processes; i++)
			if(!finished[i])
				is_finished = 0;
	}
	printf("\n");
}

int main()
{
	printf("Enter the number of processes : ");
	scanf("%d", &Number_o_Processes);

	printf("Enter the number of resource types : ");
	scanf("%d", &Number_o_Res_Types);

	printf("Enter the total resource count for each type :\n");
	for(int i = 0; i<Number_o_Res_Types; i++)
		scanf("%d", &resource_count[i]);

	printf("\nEnter the claim matrix of each process for each resource:\n");
	for(int i = 0; i<Number_o_Processes; i++)
		for(int j = 0; j<Number_o_Res_Types; j++)
			scanf("%d",&claim[i][j]);
	
	printf("\nEnter the resources of each type allotted to each process :\n");
	for(int i = 0; i<Number_o_Processes; i++)
		for(int j = 0; j<Number_o_Res_Types; j++)
			scanf("%d", &alloc[i][j]);

	int status = find_available();

	if(!status)
	{
		printf("More resources are allocated than available!!\n");
		exit(0);
	}

	printf("Available resource count :\n");
	for(int i = 0; i<Number_o_Res_Types; i++)
		printf("%d\t",available[i] );
	printf("\n");

	int state = banker();

	if(state)
	{
		printf("\nNo deadlock\n");
	}
	else 
		printf("\nDeadlock State found!!!!\n");

	return 0;
}