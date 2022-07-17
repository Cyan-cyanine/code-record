#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define err_handle(m)       \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("input like this:./exeFile [port number] [ip addr]\n");
        return -1;
    }
    int sckfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sckfd < 0)
        err_handle("socket error");
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    // addr.sin_addr.s_addr = htonl(atoi(argv[1]));
    inet_pton(AF_INET, argv[2], &addr.sin_addr);
    int ret = connect(sckfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
        err_handle("connect error");
    char buf[50];
    while (1)
    {
        bzero(buf, sizeof(buf));
        fgets(buf, sizeof(buf), stdin);
        write(sckfd, buf, sizeof(buf)); //注意：客户端用的是socket返回的套接字，而服务端使用的是accept返回的套接字
    }
    return 0;
}