#include "socket_lib.h"

PSOCKET_QUEUE CreateSocketQueue(int queueLen)
{
    PSOCKET_QUEUE pSocketQueue;

    pSocketQueue = (PSOCKET_QUEUE)malloc(sizeof(SOCKET_QUEUE));
    if(pSocketQueue==NULL)
        return NULL;

    pthread_mutex_init(&(pSocketQueue->lock),NULL);
    pthread_cond_init(&(pSocketQueue->condReadReady),NULL);

    pSocketQueue->queue = (int *)malloc(sizeof(int)*queueLen);
    if(pSocketQueue->queue==NULL){
        free(pSocketQueue);
        return NULL;
    }

    pSocketQueue->head = 0;
    pSocketQueue->tail = 0;
    pSocketQueue->queueLen = queueLen;

    return pSocketQueue;

}

void FreeSocketQueue(PSOCKET_QUEUE pSocketQueue)
{
    if(pSocketQueue){
        if(pSocketQueue->queue)
            free(pSocketQueue->queue);
        free(pSocketQueue);
    }
}

int QueueIsFull(PSOCKET_QUEUE pSocketQueue)
{
    if((pSocketQueue->tail+1)%(pSocketQueue->queueLen)==pSocketQueue->head)
        return 1;
    else 
        return 0;
}

int QueueIsEmpty(PSOCKET_QUEUE pSocketQueue)
{
    if(pSocketQueue->head==pSocketQueue->tail)
        return 1;
    else
        return 0;
}

int PushSocketInQueue(PSOCKET_QUEUE pSocketQueue, int socketfd)
{
    if(pSocketQueue==NULL)
        return -1;

    pthread_mutex_lock(&(pSocketQueue->lock));

    if(QueueIsFull(pSocketQueue)){
        pthread_mutex_unlock(&(pSocketQueue->lock));
        return -1;
    }

    pSocketQueue->queue[pSocketQueue->tail] = socketfd;
    pSocketQueue->tail = (pSocketQueue->tail+1)%(pSocketQueue->queueLen);
    
    pthread_cond_signal(&(pSocketQueue->condReadReady));
    pthread_mutex_unlock(&(pSocketQueue->lock));

    return 0;
}

int PopSocketFromQueue(PSOCKET_QUEUE pSocketQueue, int *pSocket)
{
    if(pSocketQueue==NULL)
        return -1;

    pthread_mutex_lock(&(pSocketQueue->lock));

    if(QueueIsEmpty(pSocketQueue)){
        pthread_cond_wait(&(pSocketQueue->condReadReady),&(pSocketQueue->lock));
    }
    

    *pSocket = pSocketQueue->queue[pSocketQueue->head];
    pSocketQueue->head = (pSocketQueue->head+1)%(pSocketQueue->queueLen);

    pthread_mutex_unlock(&(pSocketQueue->lock));
    return 0;
}




