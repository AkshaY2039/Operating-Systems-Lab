#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include "Scheduler.h"

using namespace std;

void Scheduler::Files_As_Processes()
{
	ifstream File_Pointer;
    system("ls ProcessFile_*.txt | wc -w > Temp.txt");
    File_Pointer.open("Temp.txt");
    File_Pointer>>Number_of_Processes;
    File_Pointer.close();
    cout<<"The number of processes in total: "<<Number_of_Processes<<endl;

    for(int i=0;i<Number_of_Processes;i++)
    {
    	char Command_To_Parse[100]="";
    	sprintf(Command_To_Parse, "stat -c%%Y ProcessFile_%d.txt > Temp.txt", i+1);
        system(Command_To_Parse);
        File_Pointer.open("Temp.txt");
        File_Pointer>>Arrival_Time[i];
        File_Pointer.close();
        
        File_Pointer.open("Temp.txt");
        sprintf(Command_To_Parse, "wc -w ProcessFile_%d.txt > Temp.txt | cut -f1 -d' ' > Temp.txt", i+1);
        system(Command_To_Parse);
        File_Pointer>>Service_Time[i];
        File_Pointer.close();
    }
	
	cout<"Read Arrival_Time, Service_Time respectively are:\n";
	for(int i=0;i<Number_of_Processes;i++)
	{
		Process_ID[i]=i+1;
		cout<<"\nFor Process ID : "<<Process_ID[i]<<endl;
		cout<<"Arrival_Time:\t"<<Arrival_Time[i]<<endl;
		cout<<"Service_Time:\t"<<Service_Time[i]<<endl;
	}
}