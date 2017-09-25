// Case conversion using pipes
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int piped[2];

	pid_t pid;
	char string[2048], buffer[4096];

	pipe(piped);

	if ((pid = fork()) < 0)
	{
		perror("Error in forking");
		exit(1);
	}

	FILE *fp;

	int bytesread;
	char var[2048];

	if (pid != 0)
	{
		printf("Parent Process : %d\n", getpid());

		//pid process closed input side
		close(piped[0]);

		fp = fopen("Text.txt", "r");

		//take input from file

		while (fscanf(fp, "%s\n", string) != EOF)
		{
			strcat(var, string);
			strcat(var, " ");
		}
		strcat(var, "\0");

		// now send string through the output side
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
		for (int i = 0; i < bytesread; ++i)
			if (isalpha(buffer[i]))
				if(islower(buffer[i]))
					buffer[i] = toupper(buffer[i]);
				else
					buffer[i] = tolower(buffer[i]);
		
		printf("Received string from parent is : \n\n%s\n\n", buffer);

		close(piped[0]);
	}
	return 0;
}