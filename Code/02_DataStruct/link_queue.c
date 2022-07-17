#include "link_queue.h"

LinkQueue* createQueue() {
    LinkQueue* newQ = malloc( sizeof( *newQ ) );
    if ( newQ == NULL )
        err_handle( "malloc erro" );
    newQ->head = newQ->tail = NULL;
    return newQ;
}

void EnQueue( LinkQueue* q, const ElemType data ) {  //入队
    LinkNode* new = malloc( sizeof( *new ) );
    if ( new == NULL )
        err_handle( "malloc error" );
    strcpy(new->data, data);
    new->next = NULL;
    if ( q->tail == NULL )
        q->tail = q->head = new;
    else {
        q->tail->next = new;
        q->tail       = new;
    }
}

bool isEmpty( LinkQueue* queue ) {
    if ( queue->head == NULL )
        return true;
    return false;
}

void DeQueue( LinkQueue* queue, ElemType data ) {  //出队
    if ( isEmpty( queue ) ) {
        return;
    }
    LinkNode* tmp;
    strcpy(data, queue->head->data);
    if ( queue->head == queue->tail ) {
        free( queue->head );
        queue->head = queue->tail = NULL;
        return;
    }
    tmp         = queue->head;
    queue->head =tmp->next;
    free( tmp );
    tmp = NULL;
    return;
}


void printQueueMember( LinkQueue* queue ) {
    if ( isEmpty( queue ) ) {
        printf("is Empty\n");
        return;
    }
    LinkNode* pos = queue->head;
    while ( pos != NULL ) {
        printf( "%s ", pos->data );
        pos = pos->next;
    }
    putchar( 10 );
}

void destroyQueue( LinkQueue* queue ) {
    if ( isEmpty( queue ) )
        return;
    LinkNode* tmp = queue->head;
    while ( 1 ) {
        tmp = queue->head->next;
        free( queue->head );
        if ( tmp == NULL ) {
            queue->head = queue->tail = tmp = NULL;
            return;
        }
        queue->head = tmp;
    }
}

// int main() {
//     char bufIn[256];
//     char bufOut[256];
//     LinkQueue* head = createQueue();
//     for ( int i = 0; i < 10; ++i ) {
//         bzero(bufIn, sizeof(bufIn));
//         sprintf(bufIn, "%dxxxx",i+1);
//         EnQueue( head, bufIn);
//         DeQueue(head, bufOut);
//         printf("%s ",bufOut);
//     }
//     putchar(10);
//     destroyQueue(head);
//     return 0;
// }
