#ifndef SIGNAL_LIST
#define SIGNAL_LIST

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define err_handle( m ) \
    do {                \
        perror( m );    \
        exit( -1 );     \
    } while ( 0 )

#define ElemType  int

typedef struct node {
    ElemType data;
    struct node* next;
} Node, *NODE;

#endif
