#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 50

static int s_iCount;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thread_funcB(void *pArg)
{
    sleep(1);

    pthread_mutex_lock(&mutex);
    s_iCount ++;
    pthread_mutex_unlock(&mutex);

    printf("%s count: %d \n", __func__, s_iCount);
    return NULL;
}

static void *thread_funcA(void *pArg)
{
    sleep(1);
    pthread_mutex_lock(&mutex);
    s_iCount++;
    pthread_mutex_unlock(&mutex);

    printf("%s count: %d\n",__func__, s_iCount);
    return NULL;
}

int main(int argc, char *argv[])
{

    pthread_t threadIDA,threadIDB;

    pthread_create(&threadIDA, NULL, &thread_funcA, NULL);
    pthread_create(&threadIDB, NULL, &thread_funcB, NULL);

    pthread_join(threadIDA,NULL);
    pthread_join(threadIDB,NULL);

}
