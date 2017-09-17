// Example 13 for forking and understanding how the process tree gets created when fork is use in comparison
// remember that fork return 0 to child and >0 to parent in case of successful forking
// AND needs one 0 to fail
// OR need one 1 to success
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	if(fork()&&fork()) //fork1 && fork2
		fork(); //fork3
	if(fork()||fork()) //fork4 || fork5
		fork(); //fork6
	printf("HI GUYS\n"); //common to all processes
	return 0;
}
