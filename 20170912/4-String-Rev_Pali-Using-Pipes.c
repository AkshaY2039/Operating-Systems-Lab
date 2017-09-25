// String reversal and palindrome check using pipes / shared memory.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void palindrome_check(char* s)
{
	int j=strlen(s),i=0;
	char r[j];
	while(s[i] != '\0')
	{
		r[j - i - 1] = s[i];
		i++;
	}
	r[j] = '\0';

	printf("Reversed : %s\n",r);

	if (strcmp(r,s) == 0)
	{
		printf("\nIt is a Palindrome\n");
	}
	else
	{
		printf("It is not a palindrome\n");
	}
}


int main()
{
	int piped[2]; // for pipes. [0] is used to read and [1] for write

	pid_t pid;
	char string[80], buffer[160];

	pipe(piped);

	if((pid = fork()) < 0)
	{
		perror("Error in forking.");
		exit(1);
	}

	int bytesread;

	if (pid != 0)
	{
		printf("Parent Process : %d\n", getpid());

		// Child process closes input side
		close(piped[0]);

		printf("Enter the string: ");
		scanf("%s",string);

		// Now send string through the output side of the pipe which is [1]
		printf("Sending string to Child is : \n\n%s\n\n", string);
		write(piped[1], string, (strlen(string) + 1));
		close(piped[1]);

		//waitpid(pid, NULL, 0);
	}
	else
	{
		printf("Child Process: %d\n", getpid());

		// parent process blocks the output side of the pipe
		close(piped[1]);

		bytesread = read(piped[0], buffer, sizeof(buffer));
		printf("Received string from parent is : \n\n%s\n\n", buffer);
		palindrome_check(buffer);

		// close all the ends after the required task is done.
		close(piped[0]);
	}
	return 0;
}