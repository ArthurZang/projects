#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>

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

    sem = sem_open(SEM_NAME,O_CREAT|O_RDWR);
    
    mysem("abcd");
    sem_post(sem);

    return 0;
}
