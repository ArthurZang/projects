#include <stdlib.h>
#include <string.h>
#include "common_include.h"
#include "queue.h"

static Queue *pQueue;

Queue * Queue_Create(int queueLen)
{
    Queue *pQueue;

    pQueue = (Queue *)malloc(sizeof(Queue));
    if(pQueue==NULL)
        return NULL;

    pQueue->pData = (char *)malloc(queueLen*sizeof(int));
    if(pQueue->pData==NULL){
        free(pQueue);
        return NULL;
    }

    memset((void*)(pQueue->pData),0,sizeof(int)*queueLen);
    pQueue->queueLen = queueLen;
    pQueue->emptyFlag = TRUE;
    pQueue->fullFlag = FALSE;
    pQueue->readIndex = 0;
    pQueue->writeIndex = 0;

    return pQueue;
}

int queue_push(Queue *pQueue, int data)
{
    if(pQueue==NULL)
        return FALSE;

    if(pQueue->fullFlag)
        return FALSE;

    pQueue->pData[pQueue->writeIndex] = data;
    pQueue->writeIndex++;
    pQueue->writeIndex%=pQueue->queueLen;

    pQueue->emptyFlag = 0;
    if(pQueue->writeIndex==pQueue->readIndex)
        pQueue->fullFlag=1;

    return TRUE;
}

int queue_pop(Queue *pQueue, int *pData)
{
    if(pQueue==NULL || pData==NULL)
        return FALSE;

    if(pQueue->emptyFlag)
        return FALSE;

    *pData = pQueue->pData[pQueue->readIndex];
    pQueue->readIndex++;
    pQueue->readIndex%=pQueue->queueLen;

    pQueue->fullFlag = 0;
    if(pQueue->readIndex==pQueue->writeIndex)
        pQueue->emptyFlag = 1;

    return TRUE;
}

void queue_delete(Queue *pQueue)
{
    if(pQueue){
        if(pQueue->pData)
            free(pQueue->pData);
        free(pQueue);
    }
}




