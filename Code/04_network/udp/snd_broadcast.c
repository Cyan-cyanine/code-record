#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//向广播地址192.168.11.255 + 10086(端口)发送信息
#define BROADCAST_IP "192.168.11.255"
#define BROADCAST_PORT 10086

#define err_handle(m)                                                          \
    {                                                                          \
        do {                                                                   \
            perror(m);                                                         \
            exit(-1);                                                          \
        } while (0);                                                           \
    }

int main(int argc, char **argv) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        err_handle("socket error");
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);
    dest_addr.sin_port = htons(BROADCAST_PORT);
    int flag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));
    // char buf[BUFSIZ] = "information from sender";
    char buf[BUFSIZ];
    while(1)
    {
        fgets(buf, BUFSIZ, stdin);
        buf[strlen(buf)-1] = 0;
        int ret = sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if(ret == -1)
            err_handle("sendto failed\n");
        sleep(1);
    }
    return 0;
}