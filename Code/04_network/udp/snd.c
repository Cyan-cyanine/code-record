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

//向192.168.11.90(主机) + 10086(端口) 发送消息
#define DEST_PORT 10086
#define DEST_IP "192.168.11.90"

#define err_handle(m) \
    do                \
    {                 \
        perror(m);    \
        exit(-1);     \
    } while (0)

int main(int argc, char **argv)
{
    int cnfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cnfd == -1)
        err_handle("socket error");

    struct sockaddr_in dest_addr;
    bzero(&dest_addr, sizeof(dest_addr));
    inet_pton(AF_INET, DEST_IP, &dest_addr.sin_addr);
    dest_addr.sin_port = htons(DEST_PORT);
    dest_addr.sin_family = AF_INET;

    char buf[BUFSIZ];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = 0;
        sendto(cnfd, buf, sizeof(buf)+1, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    }
    return 0;
}