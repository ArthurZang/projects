#include "socket_lib.h"


int main(int argc, char *argv[])
{
    int socketClient, ret;
    char pBuf[1024];
    int port = atoi(argv[1]);
    
    socketClient = CreateClientSocket("127.0.0.1", port);
    if(socketClient<1){
        printf("create client socket error\n");
        return 0;
    }
    printf("create client socket %d\n", socketClient);
    
    memset(pBuf,0,sizeof(pBuf));    
    strcpy(pBuf, "hello world");    
    ret = write(socketClient, pBuf, strlen(pBuf));
    printf("client send %d data\n",ret);
    read(socketClient,pBuf, sizeof(pBuf));
    printf("receive from server %s\n", pBuf);
    close(socketClient);
    
}


