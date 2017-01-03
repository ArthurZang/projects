#ifndef __SOCKET_QUEUE_H__
#define __SOCKET_QUEUE_H__

typedef struct{
    int *queue;
    int queueLen;
    int head;
    int tail;
    pthread_mutex_t lock;
    pthread_cond_t condReadReady;

}SOCKET_QUEUE, *PSOCKET_QUEUE;

PSOCKET_QUEUE CreateSocketQueue(int queueLen);
void FreeSocketQueue(PSOCKET_QUEUE pSocketQueue);
int QueueIsFull(PSOCKET_QUEUE pSocketQueue);
int QueueIsEmpty(PSOCKET_QUEUE pSocketQueue);
int PushSocketInQueue(PSOCKET_QUEUE pSocketQueue, int socketfd);
int PopSocketFromQueue(PSOCKET_QUEUE pSocketQueue, int *pSocket);


#endif
