#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#define Resource1 "/Res1"
#define Resource2 "/Res2"

sem_t *Sem1, *Sem2;
char Progname[20];

void sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n%s:received SIGINT\n", Progname);
        sem_post(Sem1);
        printf("%s:Released Resource1\n", Progname);
        printf("killing the process.\n");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    strcpy(Progname, argv[0]);
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    if((Sem1 = sem_open(Resource1, O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
        printf("Error Creating Resource 1\n");

    if((Sem2 = sem_open(Resource2, O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
        printf("Error Creating Resource 2\n");

    sem_wait(Sem2);
    printf("%s Acquired Resource2\n", Progname);

    sleep(3);
    printf("%s is trying to acquire Resource2\n", Progname);

    sem_wait(Sem1);

    printf("Deadlock resolved\n");
    printf("%s got Resource1\n", Progname);

    sem_post(Sem1);
    sem_post(Sem2);

    sem_unlink(Resource1);
    sem_unlink(Resource2);
}