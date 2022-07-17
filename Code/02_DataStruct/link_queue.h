#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ElemType char*

#define err_handle( m ) \
    do {                \
        perror( m );    \
        exit( -1 );     \
    } while ( 0 )

typedef struct LinkNode {
    char data[256];
    struct LinkNode* next;
}LinkNode;

typedef struct queueList{
    LinkNode *head, *tail;
}LinkQueue;

//函数声明
LinkQueue* createQueue();
void EnQueue( LinkQueue* q, const ElemType data );
bool isEmpty( LinkQueue* queue );
void printQueueMember( LinkQueue* queue );
void DeQueue( LinkQueue* queue, ElemType data );
void destroyQueue( LinkQueue* queue );

#endif
