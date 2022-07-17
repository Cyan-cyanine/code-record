#include "../../02_DataStruct/link_queue.h"  //链式队列操作
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME_LIMIT 128  //单文件长度限制

LinkQueue* queue;

void dirHandle( char* path, int pathLen );

void fileHandle( char* path) {
    if ( path == NULL )
        return;
    char curPath[FILENAME_LIMIT];
    struct stat st;
    char *p,*q;
    bzero(curPath, FILENAME_LIMIT);
    bzero( &st, sizeof( st ) );
    stat( path, &st );
    q = &path[strlen(path)];
    p = q-1;
    while(*(p-1)!='/')
        p--;
    memcpy(curPath, p, q-p);

    if ( S_ISREG( st.st_mode ) ) {
        printf( "%s   ", curPath );
    }
    else if ( S_ISDIR( st.st_mode ) ) {
        printf( "%s ", curPath );
        EnQueue( queue, path );
    }
}
void dirHandle( char* path, int pathLen ) {
    char* curPath = malloc( pathLen + FILENAME_LIMIT );
    strcpy( curPath, path );
    DIR* dir_p = opendir( curPath );
    if ( dir_p == NULL )
        err_handle( "opendir error" );
    struct dirent* dirent_p;
    printf( "%s:\n", curPath );
    if ( curPath[ pathLen - 1 ] == '/' ) {
        curPath[ pathLen - 1 ] = 0;
        pathLen--;
    }
    while ( ( dirent_p = readdir( dir_p ) ) != NULL ) {
        if ( strcmp( dirent_p->d_name, "." ) == 0 || strcmp( dirent_p->d_name, ".." ) == 0 )
            continue;
        strcat( curPath, "/" );
        strcat( curPath, dirent_p->d_name );
        fileHandle( curPath);
        curPath[ pathLen ] = 0;
    }
    printf("\n\n");
    free( curPath );
}

int main( int argc, char** argv ) {
    char tmp[ FILENAME_LIMIT ];
    queue = createQueue();
    while ( --argc ) {
        if ( strcmp( argv[ argc ], "." ) == 0 || strcmp( argv[ argc ], "./" ) == 0 )
            EnQueue( queue, argv[ argc ] );
        else {
            struct stat st;
            bzero( &st, sizeof( st ) );
            stat( argv[ argc ], &st );
            if ( S_ISREG( st.st_mode ) ) {
                printf( "%s ", argv[ argc ] );
            }
            else if ( S_ISDIR( st.st_mode ) ) {
                EnQueue( queue, argv[ argc ] );
            }
        }
    }
    putchar(10);
    while ( !isEmpty( queue ) ) {
        DeQueue( queue, tmp );
        dirHandle( tmp, strlen( tmp ) );
    }
    destroyQueue( queue );
    return 0;
}