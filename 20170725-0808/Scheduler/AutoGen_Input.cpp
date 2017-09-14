#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Scheduler.h"

using namespace std;

void Scheduler::AutoGen_Input()
{
	cout<<"\nEnter the number of processes\n";
	cin>>Number_of_Processes;
	srand(time(NULL));
	cout<"Generated Arrival_Time, Service_Time respectively are:\n";
	for(int i=0;i<Number_of_Processes;i++)
	{
		Process_ID[i]=i+1;
		cout<<"\nFor Process ID : "<<Process_ID[i]<<endl;
		Arrival_Time[i]=rand()%(2*Number_of_Processes);
		cout<<"Arrival_Time:\t"<<Arrival_Time[i]<<endl;
		Service_Time[i]=rand()%(4*Number_of_Processes)+1;
		cout<<"Service_Time:\t"<<Service_Time[i]<<endl;
	}
}