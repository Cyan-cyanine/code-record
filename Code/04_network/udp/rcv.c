#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <fcntl.h>

//监听(bind)任意网卡地址的10086端口的信息
#define LISTEN_IP "0.0.0.0"
#define LISTEN_PORT 10086


#define err_handle(m) \
    do                \
    {                 \
        perror(m);    \
        exit(-1);     \
    } while (0)

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("input like this:./exeFile [port number]\n");
        return -1;
    }
    int cnfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cnfd < 0)
        err_handle("socket error");

    struct sockaddr_in srv_addr, cli_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(LISTEN_PORT);
    srv_addr.sin_addr.s_addr = inet_addr(LISTEN_IP);
    int ret = bind(cnfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (ret == -1)
        err_handle("bind error");

    char buf[BUFSIZ]; //接收信息缓冲区
    socklen_t cli_addr_len = sizeof(cli_addr);
    while (1)
    {
        bzero(buf, sizeof(buf));
        recvfrom(cnfd, buf, BUFSIZ, 0, (struct sockaddr *)&cli_addr, &cli_addr_len);
        printf("[rcv from %s]:%s\n", inet_ntoa(cli_addr.sin_addr), buf);
    }
    return 0;
}