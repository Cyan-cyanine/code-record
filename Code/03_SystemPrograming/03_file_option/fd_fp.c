#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// fd转fp
void fd2fp(int argc, char *argv[])
{
    int fd;
    fd = open("/home/super_bert/test.dat", O_CREAT | O_RDWR, 0666); /*得到文件描述符*/
    if (-1 == fd)
    {
        perror("open file error.");
        exit(1);
    }
    else
    {
        printf("open file successfully...\n");
    }
    FILE *fp = NULL;
    fp = fdopen(fd, "r"); /*文件描述符转换为文件指针*/
    if (NULL == fp)
    {
        perror("fd to fp error.");
    }
    else
    {
        printf("transform successfully...\n");
        exit(1);
    }
}
// fp转换为fd
int fp2fd(int argc, char *argv[])
{
    FILE *fp = NULL;
    fp = fopen("/home/super_bert/test.dat", "r"); /*得到文件指针*/
    if (fp == NULL)
    {
        perror("open file error.");
        exit(1);
    }
    else
    {
        printf("open file successfully...\n");
    }

    int fd;
    fd = fileno(fp); /*文件指针转换为文件描述符*/
    if (-1 == fd)
    {
        perror("fp to fd error.");
    }
    else
    {
        printf("transform successfully...\n");
        exit(1);
    }

    return 0;
}

int main(int argc, char **argv)
{
    return 0;
}
