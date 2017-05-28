#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd;
    char *buf="world";
    
    fd = open("test.dat",O_CREAT|O_RDWR);
    if(fd<=0){
        printf("open failed\n");
        return 1;
    }

    write(fd, buf, sizeof(buf));
    close(fd);
}
