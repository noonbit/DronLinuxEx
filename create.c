#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define  BUFSIZE    100

int main(int argc, char *argv[])
{
    int fd, count;
    char wbuf[BUFSIZE], rbuf[BUFSIZE];

    printf("argv[0] = %s \n", argv[0]);
    printf("argv[1] = %s \n", argv[1]);
    
    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, \
        S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);

    if(fd == -1)
    {
        printf("File error !! \n");
        return -1;
    }

    sprintf(wbuf, "Do not count the before they hatch.");
    printf("%s\n", wbuf);
    count = write(fd, wbuf, strlen(wbuf));
    if(count <= 0) 
    {
        printf("File write error !! \n");
        return -1;
    }

    lseek(fd, 0, SEEK_SET);		// 커서 위치를 특정위치로 
    memset(rbuf, 0, BUFSIZE);		// read buffer 초기화
    count = read(fd, rbuf, BUFSIZE);
    if(count <= 0) 
    {
        printf("File read error !! \n");
        return -1;
    }
    printf("%s\n", rbuf);

//    printf("fd = %d \n", fd);

    close(fd);
}
  
