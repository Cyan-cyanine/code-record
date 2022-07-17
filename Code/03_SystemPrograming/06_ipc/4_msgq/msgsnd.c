#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MSG_SIZE 50

struct msgbuf
{
    long mtype;
    char mtext[MSG_SIZE];
};

int main(void)
{
    int key = ftok(".", 1);
    int msgid = msgget(key, IPC_CREAT | 0666);
    struct msgbuf info;
    info.mtype = 1;
    while (1)
    {
        printf("send msg:");
        fgets(info.mtext,MSG_SIZE, stdin);
        msgsnd(msgid, &info, sizeof(info), 0);
        if (strncmp(info.mtext, "quit", 4) == 0)
            break;
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}