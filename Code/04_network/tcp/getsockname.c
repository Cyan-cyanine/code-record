#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    struct sockaddr_in addr1,addr2;
    bzero(&addr1, sizeof(addr1));
    bzero(&addr2, sizeof(addr2));
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }
    addr1.sin_family = PF_INET; //AF_INET == PF_INET
    addr1.sin_port = htons(10086);
    addr1.sin_addr.s_addr = inet_addr("0.0.0.0");
    int ret = bind(sockfd, (struct sockaddr *)&addr1, sizeof(addr1));
    if(ret== -1)
    {
        perror("bind error");
        exit(-1);
    }
    socklen_t len = sizeof(addr2);  //易错点，一定得赋初值
    //获取sockfd上绑定的地址信息，网络地址信息给到addr2，地址结构体长度给到len，切记len一定得给初值，否则信息无法正确被读取
    getsockname(sockfd, (struct sockaddr *)&addr2, &len);
    printf("family = %d\n", addr2.sin_family);
    printf("ip = %s\n", inet_ntoa(addr2.sin_addr));
    printf("port = %d\n", ntohs(addr2.sin_port));
    return 0;
}