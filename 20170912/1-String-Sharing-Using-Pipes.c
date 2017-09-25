// String sharing using pipe
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int piped[2]; // for pipes. [0] is used to read and [1] for write

	pid_t pid;
	char string[520], buffer[1040];

	pipe(piped);

	if((pid = fork()) < 0)
	{
		perror("Error in forking.");
		exit(1);
	}

	FILE *fp;
	int bytesread;
	char var[520]; // take string from file and put it in var

	if (pid != 0)
	{
		printf("Parent Process : %d\n", getpid());

		// Child process closes input side
		close(piped[0]);
		fp = fopen("Text.txt", "r");

		// take input from file
		while(fscanf(fp, "%s\n", string) != EOF)
		{
			strcat(var, string);
			strcat(var," ");
		}
		strcat(var,"\0");

		// Now send string through the output side of the pipe which is [1]
		printf("Sending string to Child is : \n\n%s\n\n", var);
		write(piped[1], var, (strlen(var) + 1));
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

		// close all the ends after the required task is done.
		close(piped[0]);
	}
	return 0;
}