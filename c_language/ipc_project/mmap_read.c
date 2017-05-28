#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#define FILE_LENGTH 0x100

int main(int argc, char *argv[])
{
    int fd;
    unsigned char *pMap;
    int integer;

    fd = open("mmap.dat", O_RDWR);
    if(fd<0){
        printf("open file error\n");
        return 1;
    }

    pMap = (unsigned char *)mmap(0,FILE_LENGTH, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(pMap==MAP_FAILED){
        printf("mmap failed\n");
        close(fd);
        return 1;
    }
    close(fd);

    integer = pMap[0];
    printf("value:%d\n",integer);


    munmap(pMap,FILE_LENGTH);
    return 0;
}

