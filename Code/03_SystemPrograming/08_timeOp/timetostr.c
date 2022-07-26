#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//将time_t转化为格式"2019-02-08 12:05:08"
int timetostr( const time_t ti, char* strtime, int len ) {
    struct tm* sttm;
    if((sttm = localtime( &ti )) == NULL)   return -1;
    snprintf( strtime, len, "%04u-%02u-%02u %02u:%02u:%02u", sttm->tm_year+1900, sttm->tm_mon+1, sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec );
    return 0;
}

int main( int argc, char** argv ) {
    char buf[50];
    time_t t;
    t=time(0);
    timetostr(t, buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;
}