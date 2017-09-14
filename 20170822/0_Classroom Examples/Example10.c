#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("Hello 1\n");
	fork();
	printf("Hello 2\n");
	fork();
	printf("Hello 3\n");
	return 0;
}

/*in all 4 processes and the output is:
since maybe by default parent doesn't wait for child here.
Hello 1
Hello 2
Hello 2
Hello 3
Hello 3
Hello 3
Hello 3
*/