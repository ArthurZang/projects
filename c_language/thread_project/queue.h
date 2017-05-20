#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <pthread.h>

typedef struct __Queue{
    int queueLen;
    unsigned char fullFlag;
    unsigned char emptyFlag;
    unsigned char readIndex;
    unsigned char writeIndex; 
    char *pData;
}Queue;

Queue * queue_create(int queueLen);
void queue_delete(Queue *pQueue);
int queue_push(Queue *pQueue, int data);
int queue_pop(Queue *pQueue, int *pData);
int queue_get_len(Queue *pQueue);

#endif
