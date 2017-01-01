#include "socket_lib.h"

#define MAX(a,b) (a)>(b)?(a):(b)
#define QUEUE_SIZE 20

/*Create Socket List*/

PSOCKET_LIST CreateSocketList(void)
{
    PSOCKET_LIST pSocketList = NULL;

    pSocketList = (PSOCKET_LIST)malloc(sizeof(SOCKET_LIST));
    if(pSocketList==NULL)
	    return NULL;

    pSocketList->pSocketClientList = (int *)malloc(sizeof(int)*QUEUE_SIZE);
    if(pSocketList->pSocketClientList==NULL){
	    free(pSocketList);
	    return NULL;
    }
    memset(pSocketList->pSocketClientList, 0, sizeof(int)*QUEUE_SIZE);
    pSocketList->listLen = QUEUE_SIZE;
    pSocketList->socketServer = 0;
    pSocketList->maxfd = 0;
	
    return pSocketList;
}

void FreeSocketList(PSOCKET_LIST pSocketList)
{
    if(pSocketList){
	    if(pSocketList->pSocketClientList)
	        free(pSocketList->pSocketClientList);
	    free(pSocketList);
    }
}

int GetClientSocketByIndex(PSOCKET_LIST pSocketList, int index)
{
    return pSocketList->pSocketClientList[index];
}

int PushServerSocketInList(PSOCKET_LIST pSocketList, int socketfd)
{
    if(pSocketList==NULL)
	    return 0;

    pSocketList->socketServer = socketfd;
    pSocketList->maxfd = MAX(pSocketList->maxfd , socketfd);
    return 1;
}

int PushClientSocketInList(PSOCKET_LIST pSocketList, int socketfd)
{
    int index=0;

    if(pSocketList==NULL|| pSocketList->pSocketClientList==NULL){
        printf("error  \n");
        return -1;
    }


    for(index=0;index<pSocketList->listLen;index++){
	    if(pSocketList->pSocketClientList[index]==0){
	        pSocketList->pSocketClientList[index] = socketfd;
            pSocketList->maxfd = MAX(pSocketList->maxfd , socketfd);
            return index;
	    }
    }
    printf("Socket List is Full\n");
    return -1;
}

int PopClientSocketFromList(PSOCKET_LIST pSocketList, int socketfd)
{
    int index=0;

    if(pSocketList==NULL || pSocketList->pSocketClientList==NULL)
	    return 0;

    for(index=0; index<pSocketList->listLen;index++){
	    if(pSocketList->pSocketClientList[index]==socketfd){
	        pSocketList->pSocketClientList[index]=0;

            if(pSocketList->maxfd == socketfd){
               pSocketList->maxfd = pSocketList->socketServer;
               for(index=0; index<pSocketList->listLen;index++)
                   pSocketList->maxfd = MAX(pSocketList->maxfd , socketfd);
            }
	        return 1;
	    }
    }
    return 0;
}

int CreateServerSocket(const char *pHostAddress, int port)
{
    int socketServer = -1;
    struct sockaddr_in addrServer;

    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if(socketServer < 0)
        return -1;

    bzero(&addrServer, sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr(pHostAddress);
    addrServer.sin_port = htons(port);

    if(bind(socketServer, (struct sockaddr *)&addrServer, sizeof(addrServer))==-1){
        close(socketServer);
        return -1;
    }

    if(listen(socketServer, QUEUE_SIZE)==-1){
        close(socketServer);
        return -1;
    }

    return socketServer;
}

int CreateClientSocket(const char *pAddress, int port)
{
    int socketClient, ret;
    struct sockaddr_in addrServer;

    socketClient = socket(AF_INET, SOCK_STREAM, 0);
    if(socketClient < 0)
        return -1;

    bzero(&addrServer, sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr(pAddress);
    addrServer.sin_port = htons(port);

    while(1){
        ret = connect(socketClient, (struct sockaddr *)&addrServer, sizeof(addrServer));
        if(ret == -1)
            usleep(500*1000);
        else
            return socketClient;
    }
}


