#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#define PAGE_SIZE 4096
#define FILE_LENGTH 0x100

int random_range(unsigned const low, unsigned const hight)
{
    unsigned const range = hight - low +1;
    return low+(int)(((double)range)*rand()/(RAND_MAX+1.0));
}



int main(int argc, char *argv[])
{
    int fd;
    int i;
    unsigned char *pMap;

    srand(time(NULL));

    fd = open("mmap.dat", O_RDWR|O_APPEND|O_CREAT);
    if(fd<0){
        printf("open file error\n");
        return 1;
    }
    lseek(fd, FILE_LENGTH+1,SEEK_SET);
    write(fd,"",1);
    lseek(fd,0,SEEK_SET);

    pMap = (unsigned char *)mmap(0,FILE_LENGTH, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(pMap==MAP_FAILED){
        printf("mmap failed\n");
        close(fd);
        return 1;
    }
    close(fd);

    sprintf((char*)pMap,"%d\n",random_range(-100,100));


    munmap(pMap,FILE_LENGTH);
    return 0;
}

