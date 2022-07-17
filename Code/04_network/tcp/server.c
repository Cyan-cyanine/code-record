#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define err_handle(m)                                                          \
    do {                                                                       \
        perror(m);                                                             \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

int main(int argc, char **argv) {
    int sckfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sckfd < -1)
        err_handle("socket error");

    //给套接字设置端口复用选项
    int on = 1;
    setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    //绑定sock用于建立链接的地址信息
    struct sockaddr_in srv_addr, cli_addr;
    bzero(&srv_addr, sizeof(struct sockaddr_in));
    srv_addr.sin_family = AF_INET;            //协议
    srv_addr.sin_port = htons(atoi(argv[1])); //通讯端口号
      srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//设定接收来自哪些客户ip的信息，如果为(INADDR_ANY)，则不作限制
    // int ret2 = inet_pton(AF_INET, "127.1", &srv_addr.sin_addr);
    int ret =
        bind(sckfd, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr));
    if (ret == -1)
        err_handle("bind error");
    ret = listen(sckfd, 128); //设置监听数
    if (ret == -1)
        err_handle("listen error");
    socklen_t cli_addr_len = sizeof(cli_addr);
    int cnfd = accept(
        sckfd, (struct sockaddr *)&cli_addr,
        &cli_addr_len); // accept负责接收客户端的连接请求，如果收到连接请求则返回一个已连接的套接字描述符
    if (cnfd == -1)
        err_handle("accept error");
    printf("[connect]\n");
    char info_buf[50];
    char des[50];
    int len;
    while (1) {
        bzero(info_buf, 50);
        len = read(cnfd, info_buf, 50);
        if (len == 0) {
            printf("[ 连接关闭 ]\n");
            break;
        }
        fprintf(stdout, "[From %s]:%s",
                inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, des, 50),
                info_buf);
    }
    return 0;
}
