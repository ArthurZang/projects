#ifndef __SOCKET_LIST_H__
#define __SOCKET_LIST_H__

typedef struct {
    int *pSocketClientList;
    int listLen;
    int maxfd;
    int socketServer;
}SOCKET_LIST, *PSOCKET_LIST;

PSOCKET_LIST CreateSocketList(void);

void FreeSocketList(PSOCKET_LIST pSocketList);

#define GetSocketListLen(pSocketList) (pSocketList)->listLen

#define GetServerSocketFromList(pSocketList) (pSocketList)->socketServer

#define GetMaxSocketFromList(pSocketList)  (pSocketList)->maxfd

int GetClientSocketByIndex(PSOCKET_LIST pSocketList, int index);

int PushServerSocketInList(PSOCKET_LIST pSocketList, int socketfd);

int PushClientSocketInList(PSOCKET_LIST pSocketList, int socketfd);

int PopClientSocketFromList(PSOCKET_LIST pSocketList, int socketfd);

#endif


