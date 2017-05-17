#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


static void *thread_func(void *pArg)
{
    printf("hello pthread\n");
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t threadID;

    pthread_create(&threadID, NULL, &thread_func, NULL);
    
    pthread_join(threadID,NULL);

}
