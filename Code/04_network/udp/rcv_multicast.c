#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define GROUP_IP "224.0.2.2"
//监听任意网卡ip的10086端口发来的信息
#define LISTEN_IP "0.0.0.0" //local_addr
#define LISTEN_PORT 10086   //local_addr
#define BUFSIZE 4096

#define err_handle(m)                                                          \
    do {                                                                       \
        perror(m);                                                             \
        exit(-1);                                                              \
    } while (0)

int main(int argc, char **argv) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        err_handle("socket failed");
    //设置组播信息，为套接字开放组播权限
    struct ip_mreq group_opt;
    bzero(&group_opt, sizeof(group_opt));
    group_opt.imr_interface.s_addr = inet_addr(LISTEN_IP);   //本地网卡地址
    group_opt.imr_multiaddr.s_addr = inet_addr(GROUP_IP);   //组播地址
    setsockopt(sockfd,  IPPROTO_IP, IP_ADD_MEMBERSHIP, &group_opt, sizeof(group_opt));

    //接收发送端地址信息的结构体,和本地地址信息结构体
    struct sockaddr_in sender_addr, local_addr;
    bzero(&sender_addr, sizeof(sender_addr));
    bzero(&local_addr, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = inet_addr(LISTEN_IP);
    local_addr.sin_port = htons(LISTEN_PORT);
    int ret = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if(ret == -1)
        err_handle("bind error");
    socklen_t sender_addr_len = sizeof(sender_addr);
    char buf[BUFSIZE];
    while(1)
    {
        bzero(buf,BUFSIZE);
        recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
        printf("[rcv from %s]: %s\n", inet_ntoa(sender_addr.sin_addr), buf);
    }
    return 0;
}