#include "socket_lib.h"


static int debug(int socketfd)
{
    char pBuf[1024];
    int ret;
    
    memset(pBuf,0,sizeof(pBuf));
    ret = read(socketfd, pBuf, sizeof(pBuf));
    if(ret>0)
        printf("message from %d: %s \n", socketfd, pBuf);
    return ret; 
}

int main(int argc, char *argv[])
{
    int socketServer = -1;
    PSOCKET_LIST pSocketList = NULL;
    int port = atoi(argv[1]);
    
    socketServer = CreateServerSocket("127.0.0.1", port);    
    if(socketServer<1){
        printf("create server error\n");
        return 0;
    }
    else
        printf("create server %d \n",socketServer);
 
    pSocketList = CreateSocketList();
    if(!pSocketList){
        close(socketServer);
        printf("create socket list error \n");
        return 0;
    }
    
    PushServerSocketInList(pSocketList, socketServer);
    while(1){
        int index, ret, maxfd;
        fd_set rfds;
        int socketClient;
        
        FD_ZERO(&rfds);
        
        FD_SET(socketServer, &rfds);
        
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
                ret = debug(socketClient);
                if(ret<=0){
                    close(socketClient);
                    PopClientSocketFromList(pSocketList, socketClient);
                }
                
            }
                
        }
        
        if(FD_ISSET(socketServer, &rfds)){
            int addrClientLen;
            struct sockaddr_in addrClient;
            
            socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &addrClientLen);
            if(socketClient > 0){
                printf("new client %d",socketClient);
                index = PushClientSocketInList(pSocketList,  socketClient);
                printf("push new client %d into %d\n",socketClient, index);
            }
               
            
        }
        

        
        
        
    }
    
    
    
}



