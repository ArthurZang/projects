#include "socket_lib.h"
#include <time.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int socketClient, ret,i;
    char pBuf[1024];
    int port = atoi(argv[1]);
    int clientNum = atoi(argv[2]);
    struct timespec lastTime, curTime;
    pid_t *pid;

    pid = (pid_t *)malloc(sizeof(pid_t)*clientNum);
    if(pid==NULL)
        return -1;

    memset(pid, 0, sizeof(pid_t)*clientNum);

    
    for(i=0; i<clientNum;i++){
        pid[i] = fork();
        if(pid[i]==-1)
            break;
        if(pid[i]==0){

            socketClient = CreateClientSocket("127.0.0.1", port);
            if(socketClient<1){
                printf("create client socket error\n");
                return 0;
            }
            printf("create client  %d\n", getpid());
    
            memset(pBuf,0,sizeof(pBuf));    
            strcpy(pBuf, "hello world");    
            clock_gettime(CLOCK_MONOTONIC, &lastTime);

            ret = write(socketClient, pBuf, strlen(pBuf));
    //printf("client send %d data\n",ret);
            read(socketClient,pBuf, sizeof(pBuf));
            clock_gettime(CLOCK_MONOTONIC, &curTime);

            printf("pid:%dreceive from server %d:%d\n",getpid(),curTime.tv_sec-lastTime.tv_sec,
                    curTime.tv_nsec-lastTime.tv_nsec);
    //        sleep(100);
            close(socketClient);
            return 0;
        }
    }
    for(i=0;i<clientNum;i++){
        int status;
        waitpid(pid[i],&status,0);
    }
}


