#include "socket_lib.h"

#define MAX(a,b) (a)>(b)?(a):(b)
#define RESPONSE "server response"
#define THREAD_POOL_SIZE 3 

static PSOCKET_LIST pSocketList=NULL;
static PSOCKET_QUEUE pSocketQueue=NULL;
static int pipefd[2];

static void accept_new_client(int socketServer, PSOCKET_LIST pSocketList);
static void pthread_task(void *param)
{
    int ret;
    int socketClient;
    char pBuf[1024];

    while(1){
        PopSocketFromQueue(pSocketQueue, &socketClient);
        printf(" %d: pop %d head/tail: %d %d \n", getpid(),socketClient,pSocketQueue->head, pSocketQueue->tail);

        ret = read(socketClient, pBuf, sizeof(pBuf));
        if(ret<=0){
            //printf("close client %d\n",socketClient);
            close(socketClient);
        }else{
            sleep(1);
            //printf("server receive %d:%s\n",socketClient, pBuf);
            write(socketClient,RESPONSE, strlen(RESPONSE));
            ret = write(pipefd[1], &socketClient, sizeof(socketClient));
            //printf("feedback %d \n", socketClient); 
        }
    }

}

int main(int argc, char *argv[])
{
    int socketServer = -1;
    int flags,index;
    int port = atoi(argv[1]);
    pthread_t pthreadid;
    
    socketServer = CreateServerSocket("127.0.0.1", port);    
    if(socketServer<1){
        printf("create server error\n");
        return 0;
    }
    else
        printf("create server %d \n",socketServer);
 
    flags = fcntl(socketServer, F_GETFL, 0);
    fcntl(socketServer, flags | O_NONBLOCK);

    pipe(pipefd);

    pSocketList = CreateSocketList(20);
    if(!pSocketList){
        close(socketServer);
        printf("create socket list error \n");
        return 0;
    }

    pSocketQueue = CreateSocketQueue(20);
    if(pSocketQueue==NULL){
        close(socketServer);
        FreeSocketList(pSocketList);
        printf("Socket Queue Create Error\n");
        return 0;
    }

    for(index=0; index<THREAD_POOL_SIZE;index++)
        pthread_create(&pthreadid, NULL, pthread_task, (void *)pSocketQueue);
    
    while(1){
        int ret, maxfd;
        fd_set rfds;
        int socketClient;
        
        FD_ZERO(&rfds);
        
        FD_SET(socketServer, &rfds);
        FD_SET(pipefd[0], &rfds);
        maxfd = MAX(socketServer, pipefd[0]);
        
        EachSocketInList(pSocketList, socketClient, index){
            if(socketClient>0){
                FD_SET(socketClient, &rfds);
                maxfd = MAX(maxfd, socketClient);
            }
        }
        
        ret = select(maxfd+1, &rfds, NULL, NULL, NULL);
        if(ret<=0)
            continue;

        EachSocketInList(pSocketList, socketClient, index){
            if(socketClient!=0 && FD_ISSET(socketClient, &rfds)){
                DelSocketFromList(pSocketList, socketClient);
                PushSocketInQueue(pSocketQueue, socketClient);
                //printf("push %d head/tail %d:%d \n", socketClient,pSocketQueue->head, pSocketQueue->tail);
                //for(ret=0;ret<pSocketQueue->queueLen;ret++){
                //    printf("[%d] ", pSocketQueue->queue[ret]);
                //}
                //printf("\n");
            }
                
        }
        
        if(FD_ISSET(socketServer, &rfds))
           accept_new_client(socketServer, pSocketList); 


        if(FD_ISSET(pipefd[0], &rfds)){

            read(pipefd[0], &socketClient, sizeof(socketClient));
            AddSocketInList(pSocketList, socketClient);
            //printf(" event socketClient = %d \n", socketClient);
        }
        
    }
    
    
    
}

static void accept_new_client(int socketServer, PSOCKET_LIST pSocketList)
{
    int socketClient;
    int addrClientLen,index;
    struct sockaddr_in addrClient;
    
    socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &addrClientLen);
    if(socketClient > 0){
       index = AddSocketInList(pSocketList,  socketClient);
       printf("accept new client %d into %d\n",socketClient, index);
    }
}

