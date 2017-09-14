#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	fork();
	fork()&&fork()||fork();
	fork();
	printf("Hello\n");
	return 0;
}

/*
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
Hello
akshay@Kumar ~/Desktop/SEM5LAB/OS-P/20170822/Classroom Examples $ Hello
Hello
Hello
Hello
Hello
Hello
20 prints i.e. 20 processes in all and then no termination here.. it waits..
*/