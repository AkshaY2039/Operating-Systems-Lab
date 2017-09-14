// Odd and Even Series generation in Parent Child Setup
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int a=0,b=1,n=a+b,iend;
	printf("Enter the number of terms of Fibonacci & Prime Sequence to generate:\n");
	scanf("%d",&iend);
	pid_t pid = fork();
	if (pid == 0)
	{
    	printf("Child is making the Fibonacci Series\n");
    	printf("First %d Fibonacci Terms are :\n",iend);
        if(iend>=2)
    		printf("0 %d ",n);
    	else
    		if(iend==1)
    			printf("0");
    	for(int i=3;i<=iend;i++)
    	{
	        n=a+b;
        	printf("%d ",n);
        	a=b;
        	b=n;
    	}
    	printf("\nChild ends\n");
	}
    else 
    {
        printf("Parent is waiting for child to complete...\n");
        wait(0);
        printf("Now parent generating Prime numbers\n");
        int i=3, count, c;
 
        if(iend>=1)
        {
            printf("First %d prime numbers are :\n",iend);
            printf("2 ");
        }
        for(count=2;count<=iend;)
        {
            for(c=2;c<=i-1;c++)
                if(i%c==0)
                    break;
            if(c==i)
            {
                printf("%d ",i);
                count++;
            }
            i++;
        }         
        printf("\nParent ends\n");
    }
    return 0;
}