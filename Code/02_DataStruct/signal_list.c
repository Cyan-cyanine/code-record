#include "signal_list.h"

NODE createListHead() {
    NODE head = malloc( sizeof( *head ) );
    if ( head == NULL )
        err_handle( "malloc error" );
    head->next = NULL;
    head->data = 0;
    return head;
}

NODE createNode( ElemType data ) {
    NODE new = malloc( sizeof( *new ) );
    if ( new == NULL )
        err_handle( "malloc error" );
    new->next = NULL;
    new->data = data;
    return new;
}

void insertFromTail( NODE head, NODE new ) {
    if ( head == NULL || new == NULL )
        return;
    NODE p = head;
    while ( p->next != NULL )
        p = p->next;
    p->next = new;
}

void insertFromHead( NODE head, NODE new ) {
    if ( head == NULL || new == NULL )
        return;
    new->next  = head->next;
    head->next = new;
}

NODE serchNode( NODE head, const NODE obj ) {
    if ( head == NULL || obj == NULL )
        return NULL;
    NODE p = head;
    while ( p->next != NULL && p->next->data != obj->data ) //ElemType改动时需要修改
        p = p->next;
    if(p->next == NULL)
        return NULL;
    else if(p->next->data == obj->data)
        return p;
    return NULL;
}

bool deleteNode(NODE head, NODE obj)
{
    if ( head == NULL || obj == NULL )
        return false;
    NODE p,q;
    if((p = serchNode(head, obj)) == NULL)
        return false;
    q = p->next;
    p->next = q->next;
    free(q);
    return true;
}

void destoryList(const NODE head)
{
    if(head == NULL)
        return ;
    NODE p = head->next, q;
    if(p == NULL)
        return ;
    while((q=p->next) != NULL)
    {
        free(p);
        p=q;
    }
    free(p);
    p = NULL;
    q = NULL;
    head->next = NULL;
}


void print(NODE curNode)    //若ElemType发生改变，则需要重写该函数
{
    printf("%d ", curNode->data);
}

void printList(const NODE head)
{
    if(head->next == NULL)
        return ;
    NODE p = head;
    while(p->next != NULL)
    {
        p=p->next;
        print(p);
    }
    putchar(10);
}

int main(void)
{
    NODE head = createListHead();
    Node obj = {4};
    for(int i = 0; i<10 ;i++)
    {
        NODE new = createNode(i+1);
        insertFromTail(head, new);
    }
    printList(head);
    printf("delete test\n");
    deleteNode(head, &obj);
    printList(head);
    destoryList(head);
    return 0;
}