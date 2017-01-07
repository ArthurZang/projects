#ifndef __SOCKET_LIST_H__
#define __SOCKET_LIST_H__

typedef struct {
    int *pList;
    int listLen;
}SOCKET_LIST, *PSOCKET_LIST;

PSOCKET_LIST CreateSocketList(int listLen);

void FreeSocketList(PSOCKET_LIST pSocketList);

int AddSocketInList(PSOCKET_LIST pSocketList, int socketfd);

int DelSocketFromList(PSOCKET_LIST pSocketList, int socketfd);

#define EachSocketInList(pSocketList, socketfd, index) \
    for(index=0, socketfd=pSocketList->pList[0];       \
        index<pSocketList->listLen;                    \
        index++, socketfd=pSocketList->pList[index])

#endif


