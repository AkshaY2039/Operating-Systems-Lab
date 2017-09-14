#include <iostream>
#include "Scheduler.h"

using namespace std;

void Scheduler::Manual_Input()
{
	cout<<"\nEnter the number of processes\n";
	cin>>Number_of_Processes;

	cout<"Enter Arrival_Time, Service_Time respectively:\n";
	for(int i=0;i<Number_of_Processes;i++)
	{
		Process_ID[i]=i+1;
		cout<<"\nFor Process ID : "<<Process_ID[i]<<endl;
		cout<<"Arrival_Time:\t";
		cin>>Arrival_Time[i];
		cout<<"Service_Time:\t";
		cin>>Service_Time[i];
	}
}