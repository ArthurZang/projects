#include "socket_lib.h"

static PSOCKET_LIST pSocketList=NULL;
static PSOCKET_QUEUE pSocketQueue=NULL;
static int pipefd[2];

static void accept_new_client(int socketServer, PSOCKET_LIST pSocketList);
static void pthread_task(void *param)
{
#define RESPONSE "server response"
    int ret;
    int socketClient;
    char pBuf[1024];
    uint64_t temp;

    while(1){
        PopSocketFromQueue(pSocketQueue, &socketClient);

        ret = read(socketClient, pBuf, sizeof(pBuf));
        if(ret<=0){
            printf("close client %d\n",socketClient);
            close(socketClient);
        }else{
            long temp;
        
            printf("server receive %d:%s\n",socketClient, pBuf);
            write(socketClient,RESPONSE, strlen(RESPONSE));
            PushClientSocketInList(pSocketList, socketClient);
            ret = write(pipefd[1], &temp, sizeof(temp));
            printf("event write %d\n",ret);
        }
    }



}

int main(int argc, char *argv[])
{
    int socketServer = -1;
    int flags;
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

    /*s_eventfd = eventfd(0,EFD_NONBLOCK);
    if(s_eventfd==-1){
        printf("event fd error\n");
        return 0;
    }*/
    pipe(pipefd);

    pSocketList = CreateSocketList();
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


    pthread_create(&pthreadid, NULL, pthread_task, (void *)pSocketQueue);
    
    PushServerSocketInList(pSocketList, socketServer);
    
    while(1){
        int index, ret, maxfd;
        fd_set rfds;
        int socketClient;
        
        FD_ZERO(&rfds);
        
        FD_SET(socketServer, &rfds);
        FD_SET(pipefd[0], &rfds);
        
        for(index=0; index<GetSocketListLen(pSocketList); index++){
            socketClient = GetClientSocketByIndex(pSocketList, index);
            //printf("index %d:%d", index, socketClient);
            if(socketClient>0){
                FD_SET(socketClient, &rfds);
            }
        }
        
        maxfd = GetMaxSocketFromList(pSocketList);

        ret = select(maxfd+1, &rfds, NULL, NULL, NULL);
        if(ret<=0)
            continue;
        for(index=0; index<GetSocketListLen(pSocketList); index++){
            socketClient = GetClientSocketByIndex(pSocketList, index);
            if(socketClient!=0 && FD_ISSET(socketClient, &rfds)){
                PopClientSocketFromList(pSocketList, socketClient);
                
                //printf("create pthread for client %d \n",socketClient);
                //printf(" param = %x \n",(void *)(&socketRecv));
                PushSocketInQueue(pSocketQueue, socketClient);
                
                //pthread_join(pthreadid, NULL);
                //if(ret<=0){
                //    close(socketClient);
                //    PopClientSocketFromList(pSocketList, socketClient);
                //}
                
            }
                
        }
        
        if(FD_ISSET(socketServer, &rfds))
           accept_new_client(socketServer, pSocketList); 


        if(FD_ISSET(pipefd[0], &rfds)){
            uint64_t temp;
            read(pipefd[0], &temp, sizeof(temp));
            printf(" event socketClient = %d \n", socketClient);
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
       index = PushClientSocketInList(pSocketList,  socketClient);
       printf("push new client %d into %d\n",socketClient, index);
    }
}

