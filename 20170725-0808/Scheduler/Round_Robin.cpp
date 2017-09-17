//Round Robin (PE)
#include <iostream>
#include <climits>
#include <cstdlib>
#include "Scheduler.h"

using namespace std;

struct Ready_Queue
{
	int ID;
	struct Ready_Queue *link;
}*Front=NULL,*Rear=NULL;

void enqueue(int a)
{
	Ready_Queue *Temp;
	Temp=new(struct Ready_Queue);
	Temp->ID=a;
	Temp->link=NULL;
	if(Front==NULL)
		Front=Temp;
	else
		Rear->link=Temp;
	Rear=Temp;
}

void dequeue()
{
	Ready_Queue *Temp;
    if (Front == NULL)
        cout<<"Ready_Queue Empty"<<endl;
    else
    {       
        Temp = Front;
        Front = Front->link;
        free(Temp);
    }
}

void Scheduler::Display_Ready_Queue()
{
	cout<<"\nReady Queue=\t";
	Ready_Queue *Temp=Front;
	while(Temp!=NULL)
	{
		cout<<Process_ID[Temp->ID]<<"\t";
		Temp=Temp->link;
	}
	cout<<endl<<endl;
}

void Scheduler::Round_Robin()
{
	//to avoid error when complete process table is empty
	if(Number_of_Processes>0)
	{
		Sort_By(Service_Time);
		int IsCompleted[Number_of_Processes]={0},IsQueued[Number_of_Processes]={0},Min_Arrival_Time,Min_rem,ID,Stop_Flag,Arrive_Flag,System_Time=0,Remaining_Time[Number_of_Processes],Prev_ID=Number_of_Processes;
		for(int i=0;i<Number_of_Processes;i++)
			Remaining_Time[i]=Service_Time[i];
		int Time_Quantum;
		cout<<"Enter the Time_Quantum:\n";
		cin>>Time_Quantum;
		cout<<"\nGantt Chart for Round_Robin\n";
		
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

			if(Prev_ID==Number_of_Processes)
			{
				Min_Arrival_Time=INT_MAX;
				for(int i=0;i<Number_of_Processes;i++)
					if(IsCompleted[i]==0 && Arrival_Time[i]<Min_Arrival_Time && Arrival_Time[i]<=System_Time)
					{
						Min_Arrival_Time=Arrival_Time[i];
						enqueue(i);
					}
			}
			
			//Display_Ready_Queue();
			ID=Front->ID;
			dequeue();
			
				if(Prev_ID!=ID)
				{
					Prev_ID=ID;
					cout<<"["<<System_Time<<"]_"<<Process_ID[ID]<<"_";
				}

				if(Remaining_Time[ID]<=Time_Quantum)
				{
					Completion_Time[ID]= System_Time + Remaining_Time[ID];
					Turn_Around_Time[ID]= Completion_Time[ID] - Arrival_Time[ID];
					Wait_Time[ID]= Turn_Around_Time[ID] - Service_Time[ID];
					IsCompleted[ID]=1;
					System_Time=Completion_Time[ID];
					for(int i=0;i<Number_of_Processes;i++)
						if(Arrival_Time[i]<=System_Time && IsCompleted[i]==0 && IsQueued[i]==0)
						{
							enqueue(i);
							IsQueued[i]=1;
						}
				}
				else
				{
					Remaining_Time[ID]-=Time_Quantum;
					System_Time+=Time_Quantum;
					for(int i=0;i<Number_of_Processes;i++)
						if(Arrival_Time[i]<=System_Time && IsCompleted[i]==0 && i!=ID && IsQueued[i]==0)
						{
							enqueue(i);
							IsQueued[i]=1;
						}
					enqueue(ID);
					IsQueued[ID]=1;
					continue;
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