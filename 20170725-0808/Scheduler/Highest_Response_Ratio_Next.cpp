//Highest Response Ration Next (NPE)
#include <iostream>
#include <climits>
#include "Scheduler.h"

using namespace std;

void Scheduler::Highest_Response_Ratio_Next()
{
	//to avoid error when complete process table is empty
	if(Number_of_Processes>0)
	{
		int IsCompleted[Number_of_Processes]={0},ID,Stop_Flag,Arrive_Flag,System_Time=0;
		float Response_Ratio=0,Max_Response_Ratio;
		cout<<"\nGantt Chart for Highest_Response_Ratio_Next\n["<<System_Time<<"]";
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
			
			Max_Response_Ratio=0;
			for(int i=0;i<Number_of_Processes;i++)
			{
				if(IsCompleted[i]==0 && Arrival_Time[i]<=System_Time)
				{
					Response_Ratio=(float)(System_Time-Arrival_Time[i]+Service_Time[i])/Service_Time[i];
					//cout<<"Process: "<<i+1<<"\tResponse Ratio:"<<Response_Ratio<<endl;
					if(Response_Ratio>Max_Response_Ratio)
					{
						Max_Response_Ratio=Response_Ratio;
						ID=i;
					}
				}					
			}

			Completion_Time[ID]= System_Time + Service_Time[ID];
			Turn_Around_Time[ID]= Completion_Time[ID] - Arrival_Time[ID];
			Wait_Time[ID]= Turn_Around_Time[ID] - Service_Time[ID];
			IsCompleted[ID]=1;
			System_Time= Completion_Time[ID];
			cout<<"_"<<Process_ID[ID]<<"_["<<System_Time<<"]";

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