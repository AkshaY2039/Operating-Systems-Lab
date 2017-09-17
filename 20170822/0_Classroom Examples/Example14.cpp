// Example 14 for forking in cpp and understanding how global and local variable are treated
#include <iostream>
#include <string>
#include <sys/types.h> //required for fork routine
#include <unistd.h>
#include <stdlib.h>   //header for exit()

using namespace std;

int globalVariable=2; //global variable

int main() //main module
{
	string sIdentifier; //string variable for identifying the process
	int iStackVariable=20; //local variable to main

	pid_t pID=fork(); //forking a new process
	if(pID==0) //for child process...
	{
		sIdentifier="Child Process: ";
		globalVariable++;iStackVariable++; //increment both variables by 1
	}
	else
		if(pID<0)//failed fork...
		{
			cerr<<"Failed to fork"<<endl; //into the error file
			exit(1);
		}
		else //for parent process...
			sIdentifier="Parent Process:";
	//common to both parent and child  
	cout<<sIdentifier;
	cout<<" Global variable: "<<globalVariable;
	cout<<" Stack variable: "<<iStackVariable<<endl;
	return 0;
}