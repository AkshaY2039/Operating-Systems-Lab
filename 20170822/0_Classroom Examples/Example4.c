// Example 4 for forking and understanding how the process tree gets created when fork is use in comparison
// remember that fork return 0 to child and >0 to parent in case of successful forking
// total 20 prints here
// AND needs one 0 to fail
// OR need one 1 to success
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() //main module
{
	fork(); //fork1
	fork()&&fork()||fork(); //fork2&&fork3||fork4
	fork(); //fork5
	printf("Hello\n");
	return 0;
}
