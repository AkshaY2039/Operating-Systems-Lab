#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\033[0m" //RESET COLOR

int main(int argc, char const *argv[])
{
	if(argc != 2)
		printf("Valid Usage: %s <number>\n", argv[0]);
	else
	{
		int user = atoi(argv[1]);
		int num = user%7 + 1;
		printf("\033[1;3%dm \t\t _ _ _ _ _ _ Welcome to Colors, Dear User : %d _ _ _ _ _ _ " KNRM "\n", num, user);
	}
	return 0;
}