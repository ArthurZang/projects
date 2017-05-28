#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>

#define SEM_NAME "mysem"

static sem_t *sem = NULL;

static void mysem(char *str)
{
    int i=0;
    
    while(str[i]!='\0'){
        printf("%c\n",str[i]);
        i++;
        sleep(1);
    }
}

int main(void)
{
    pid_t pid = -1;

    sem = sem_open(SEM_NAME,O_CREAT|O_RDWR, 0077, 0);
    if(sem==SEM_FAILED){
        printf("sem_open error\n");
        return 1;
    }

    sem_wait(sem);
    
    mysem("1234");
    sem_post(sem);
    sem_unlink(SEM_NAME);
    sem_close(sem);

    return 0;
}
