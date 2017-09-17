//for the formatted tabular output
#include <iostream>
#include <iomanip>
#include "Scheduler.h"

using namespace std;

void Scheduler::Sort_By(int Array[])
{
	int temp1;
	for(int i=0;i<Number_of_Processes;i++)
		for(int j=0;j<Number_of_Processes;j++)
			if(Array[i] < Array[j])
			{
				temp1= Arrival_Time[i];
				Arrival_Time[i]= Arrival_Time[j];
				Arrival_Time[j]= temp1;
				
				temp1= Service_Time[i];
				Service_Time[i]= Service_Time[j];
				Service_Time[j]= temp1;
				
				temp1= Process_ID[i];
				Process_ID[i]= Process_ID[j];
				Process_ID[j]= temp1;

				temp1= Completion_Time[i];
				Completion_Time[i]= Completion_Time[j];
				Completion_Time[j]= temp1;

				temp1= Turn_Around_Time[i];
				Turn_Around_Time[i]= Turn_Around_Time[j];
				Turn_Around_Time[j]= temp1;

				temp1= Wait_Time[i];
				Wait_Time[i]= Wait_Time[j];
				Wait_Time[j]= temp1;
			}
}

void Scheduler::Formatted_Output()
{	
	if(Number_of_Processes>0)
	{
		float Avg_Wait_Time=0;
		cout<<"\n\n";
		cout<<setw(10)<<"Process_ID";
		cout<<" | ";
		cout<<setw(12)<<"Arrival_Time";
		cout<<" | ";
		cout<<setw(12)<<"Service_Time";
		cout<<" | ";
		cout<<setw(15)<<"Completion_Time";
		cout<<" | ";
		cout<<setw(16)<<"Turn_Around_Time";
		cout<<" | ";
		cout<<setw(9)<<"Wait_Time";
		cout<<" |\n";
		cout<<string(91,'-')<<endl;
		for(int i=0;i<Number_of_Processes;i++)
		{
			cout<<setw(10)<<Process_ID[i];
			cout<<" | ";
			cout<<setw(12)<<Arrival_Time[i];
			cout<<" | ";
			cout<<setw(12)<<Service_Time[i];
			cout<<" | ";
			cout<<setw(15)<<Completion_Time[i];
			cout<<" | ";
			cout<<setw(16)<<Turn_Around_Time[i];
			cout<<" | ";
			cout<<setw(9)<<Wait_Time[i];
			cout<<" |\n";
			Avg_Wait_Time+=Wait_Time[i];
		}
		cout<<"\n\n\t\tAvg Wait Time = "<<Avg_Wait_Time/Number_of_Processes<<"\n\n";
	}
	else
		cout<<"\n\t\tProcessor Idle!!! No Process to be scheduled...\n";
}