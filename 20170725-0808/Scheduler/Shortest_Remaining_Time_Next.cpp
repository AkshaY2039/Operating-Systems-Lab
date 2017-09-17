//Shortest Remaining Time Next (PE)
#include <iostream>
#include <climits>
#include "Scheduler.h"

using namespace std;

void Scheduler::Shortest_Remaining_Time_Next()
{
	//to avoid error when complete process table is empty
	if(Number_of_Processes>0)
	{
		int IsCompleted[Number_of_Processes]={0},Min_Arrival_Time,Min_rem,ID,Stop_Flag,Arrive_Flag,System_Time=0,Remaining_Time[Number_of_Processes],Prev_ID=Number_of_Processes;
		for(int i=0;i<Number_of_Processes;i++)
			Remaining_Time[i]=Service_Time[i];
		
		cout<<"\nGantt Chart for Shortest_Remaining_Time_Next\n";
		
		while(1)
		{
			Stop_Flag=1;
			Arrive_Flag=0;
			for(int i=0;i<Number_of_Processes;i++)
				if(IsCompleted[i]==0 && Arrival_Time[i]<=System_Time)
				{
					Arrive_Flag=1;//a process has Arrived
					break;
				}
			if(Arrive_Flag==0)
			{
				cout<<"["<<System_Time<<"]";
				System_Time=INT_MAX;//no process has come yet
				for(int i=0;i<Number_of_Processes;i++)
					if(Arrival_Time[i]<=System_Time && IsCompleted[i]==0)
						System_Time=Arrival_Time[i];
				cout<<"_EMPTY_";
			}
		
			Min_rem=INT_MAX;
			for(int i=0;i<Number_of_Processes;i++)
				if(Arrival_Time[i]<=System_Time && IsCompleted[i]==0 && Remaining_Time[i]<Min_rem)
					Min_rem=Remaining_Time[i];
			
			if(Min_rem!=INT_MAX)
			{	
				Min_Arrival_Time=INT_MAX;
				for(int i=0;i<Number_of_Processes;i++)
					if(Remaining_Time[i]==Min_rem && Arrival_Time[i]<Min_Arrival_Time && IsCompleted[i]==0)
					{
						Min_Arrival_Time=Arrival_Time[i];
						ID=i;
					}

				if(Prev_ID!=ID)
				{
					Prev_ID=ID;
					cout<<"["<<System_Time<<"]_"<<Process_ID[ID]<<"_";
				}

				if(Remaining_Time[ID]<=1)
				{
					Completion_Time[ID]= System_Time + Remaining_Time[ID];
					Turn_Around_Time[ID]= Completion_Time[ID] - Arrival_Time[ID];
					Wait_Time[ID]= Turn_Around_Time[ID] - Service_Time[ID];
					IsCompleted[ID]=1;
					System_Time=Completion_Time[ID];
				}
				else
				{
					Remaining_Time[ID]--;
					System_Time++;
					continue;
				}
			}
			for(int i=0;i<Number_of_Processes;i++)
			{
				if(IsCompleted[i]==0)
				{
					Stop_Flag=0;
					break;
				}
			}

		if(Stop_Flag==1)
		{
			cout<<"["<<Completion_Time[ID]<<"]";
			break;
		}
		}
	}
}