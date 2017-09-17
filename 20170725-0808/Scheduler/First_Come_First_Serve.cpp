//First Come First Serve (NPE)
#include <iostream>
#include <climits>
#include "Scheduler.h"

using namespace std;

void Scheduler::First_Come_First_Serve()
{
	//to avoid error when complete process table is empty
	if(Number_of_Processes>0)
	{
		int IsCompleted[Number_of_Processes]={0},Min_Arrival_Time,Min_Service_Time,ID,Stop_Flag,Arrive_Flag,System_Time=0;
		cout<<"\nGantt Chart for First_Come_First_Serve\n["<<System_Time<<"]";
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
				System_Time=INT_MAX;//no process has come yet
				for(int i=0;i<Number_of_Processes;i++)
					if(Arrival_Time[i]<=System_Time && IsCompleted[i]==0)
						System_Time=Arrival_Time[i];
				cout<<"_EMPTY_["<<System_Time<<"]";
			}
			
			Min_Arrival_Time=INT_MAX;
			for(int i=0;i<Number_of_Processes;i++)
				if(IsCompleted[i]==0 && Arrival_Time[i]<Min_Arrival_Time)
					Min_Arrival_Time=Arrival_Time[i];
			
			if(Min_Arrival_Time!=INT_MAX)
			{	
				Min_Service_Time=INT_MAX;
				for(int i=0;i<Number_of_Processes;i++)
					if(Arrival_Time[i]==Min_Arrival_Time && Service_Time[i]<Min_Service_Time && IsCompleted[i]==0)
					{
						Min_Service_Time=Service_Time[i];
						ID=i;
					}

				Completion_Time[ID]= System_Time + Service_Time[ID];
				Turn_Around_Time[ID]= Completion_Time[ID] - Arrival_Time[ID];
				Wait_Time[ID]= Turn_Around_Time[ID] - Service_Time[ID];
				IsCompleted[ID]=1;
				System_Time= Completion_Time[ID];
				cout<<"_"<<Process_ID[ID]<<"_["<<System_Time<<"]";
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
			break;
		}
	}
}