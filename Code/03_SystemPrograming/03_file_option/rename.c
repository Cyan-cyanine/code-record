#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define err_handle( m ) \
    do {                \
        perror( m );    \
        exit( -1 );     \
    } while ( 0 )

int main( int argc, char** argv ) {
    if ( argc != 1 )
        err_handle( "arg error" );
    int i = 1, j = 1;
    printf("开始编号(0~10000):");
    scanf("%d",&i);
    j = i;
    if ( i < 0 || i > 10000 )
        return -1;
    char png[ 128 ];
    char jpg[ 128 ];
    DIR* dir_p = opendir( "." );
    if ( dir_p == NULL )
        err_handle( "opendir error" );
    struct dirent* dirent_p;
    char*          p;
    struct stat    st;
    while ( ( dirent_p = readdir( dir_p ) ) != NULL ) {
        if ( strcmp( dirent_p->d_name, "." ) == 0 || strcmp( dirent_p->d_name, ".." ) == 0 )
            continue;
        p = &( dirent_p->d_name[ strlen( dirent_p->d_name ) - 4 ] );
        bzero( &st, sizeof( st ) );
        sprintf( png, "%d.png", i );
        sprintf( jpg, "%d.jpg", j );
        if ( access( png, F_OK ) == 0 || access(jpg, F_OK) == 0)
            continue;
        if ( strcmp( p, ".png" ) == 0 ) {
            printf( "%s->\t%s\n", dirent_p->d_name, png );
            rename( dirent_p->d_name, png );
            i++;
        }
        else if (strcmp( p, ".jpg" ) == 0) {
            printf( "%s->\t%s\n", dirent_p->d_name, jpg );
            rename( dirent_p->d_name, jpg );
            j++;
        }
    }
    return 0;
}