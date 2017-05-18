#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 50

static int s_iCount;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thread_func(void *pArg)
{
    sleep(1);

    pthread_mutex_lock(&mutex);
    s_iCount ++;
    pthread_mutex_unlock(&mutex);

    printf("hello pthread %d \n", s_iCount);
    return NULL;
}
int main(int argc, char *argv[])
{
    int i;

    pthread_t threadID[THREAD_NUM];

    for(i=0;i<THREAD_NUM;i++){
        pthread_create(&threadID[i], NULL, &thread_func, NULL);
    }

    for(i=0;i<THREAD_NUM;i++)
        pthread_join(threadID[i],NULL);

}
