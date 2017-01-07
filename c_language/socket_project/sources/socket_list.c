#include "socket_lib.h"

#define MAX(a,b) (a)>(b)?(a):(b)
#define QUEUE_SIZE 20

/*Create Socket List*/

PSOCKET_LIST CreateSocketList(int listLen)
{
    PSOCKET_LIST pSocketList = NULL;

    pSocketList = (PSOCKET_LIST)malloc(sizeof(SOCKET_LIST));
    if(pSocketList==NULL)
	    return NULL;

    pSocketList->pList = (int *)malloc(sizeof(int)*listLen);
    if(pSocketList->pList==NULL){
	    free(pSocketList);
	    return NULL;
    }
    memset(pSocketList->pList, 0, sizeof(int)*QUEUE_SIZE);
    pSocketList->listLen = listLen;
	
    return pSocketList;
}

void FreeSocketList(PSOCKET_LIST pSocketList)
{
    if(pSocketList){
	    if(pSocketList->pList)
	        free(pSocketList->pList);
	    free(pSocketList);
    }
}


int AddSocketInList(PSOCKET_LIST pSocketList, int socketfd)
{
    int index=0;

    if(pSocketList==NULL|| pSocketList->pList==NULL){
        printf("error  \n");
        return -1;
    }


    for(index=0;index<pSocketList->listLen;index++){
	    if(pSocketList->pList[index]==0){
	        pSocketList->pList[index] = socketfd;
            return 0;
	    }
    }
    printf("Socket List is Full\n");
    return -1;
}

int DelSocketFromList(PSOCKET_LIST pSocketList, int socketfd)
{
    int index=0;

    if(pSocketList==NULL || pSocketList->pList==NULL)
	    return -1;

    for(index=0; index<pSocketList->listLen;index++){
	    if(pSocketList->pList[index]==socketfd){
	        pSocketList->pList[index]=0;
            return 0;
        }
    }
    return -1;
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


