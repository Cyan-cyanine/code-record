#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GROUP_PORT 10086
#define GROUP_IP "224.0.2.2"
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
    group_opt.imr_interface.s_addr = INADDR_ANY;   //本地网卡地址
    group_opt.imr_multiaddr.s_addr = inet_addr(GROUP_IP);   //组播地址
    int ret = setsockopt(sockfd,  IPPROTO_IP, IP_ADD_MEMBERSHIP, &group_opt, sizeof(group_opt));
    if(ret == -1)
        err_handle("setsockopt error");
    //设置目标地址结构体
    struct sockaddr_in dest_addr;
    bzero(&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(GROUP_IP);
    dest_addr.sin_port = htons(GROUP_PORT);
    char buf[BUFSIZE];
    while(1)
    {
        bzero(buf, BUFSIZE);
        fgets(buf,BUFSIZE, stdin);
        buf[strlen(buf)-1] = 0;
        sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    }
    return 0;
}