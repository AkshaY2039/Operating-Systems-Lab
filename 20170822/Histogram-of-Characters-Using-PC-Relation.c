/*Histogram printing of characters in a given text.
 calculating frequency in one process & checking new character in other*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHAR_NOS 128

int main()
{
	char string[1024];
	printf("Enter the string: ");
	gets(string);

	int freq[CHAR_NOS]={0};
	pid_t pid = vfork();
	if(pid < 0)
	{
		printf("Failed Fork\n");
		exit(0);
	}
	else
		if(pid == 0)
		{
			printf("\nChild is calculating the frequency of each character\n");
			int i=0;
			while(string[i] != '\0')
			{
				int index = (int)(string[i]);
				freq[index]++;
				i++;
			}
			printf("\nChild finished the task\n");
			exit(0);
		}
		else
		{
			printf("\nParent is waiting for Child\n");
			wait(0);
			printf("Character Histogram for the string:\n%s\n------->\n", string);
			for(int i = 0; i < CHAR_NOS; i++)
				if(freq[i])
				{
					printf("'%c' ", (char)(i));
					for(int k = 0; k < freq[i]; k++)
						printf("#");
					printf(" -- %d\n", freq[i]);
				}
		}
	return 0;
}