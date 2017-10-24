/* program for Histogram using pthread */
/* compile with the "-pthread" option*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define CHAR_NOS 128

char string[1024];

void *frequency(void *param)
{
	int count = 0, i = 0;
	int c = *(int *)param;
	while(string[i] != '\0')
	{
		if((int)string[i] == c)
			count++;
		i++;
	}
	if(count)
		printf("Thread : %lu found the frequency of '%c' to be %d...\n", pthread_self(), c, count);
	pthread_exit(0);
}

int main()
{
	printf("Enter the string: ");
	gets(string);

	int ASCII[CHAR_NOS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t freq_t[CHAR_NOS];
	
	for(int i = 0; i < CHAR_NOS; i++)
	{
		ASCII[i] = i;
		pthread_create(&freq_t[i], &attr, frequency, &ASCII[i]);
	}
	for(int i = 0; i < CHAR_NOS; i++)
		pthread_join(freq_t[i], NULL);
	
	return 0;
}