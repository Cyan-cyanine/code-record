#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//整数转字符串
int timetostr( const time_t ti, char* strtime, int len ) {
    struct tm* sttm;
    if((sttm = localtime( &ti )) == NULL)   return -1;
    snprintf( strtime, len, "%04u-%02u-%02u %02u:%02u:%02u", sttm->tm_year+1900, sttm->tm_mon+1, sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec );
    return 0;
}

//字符串转整数
int strtotime(const char *strtime, int len, time_t *ti){
    struct tm sttm;
    bzero(&sttm, sizeof(struct tm));
    sscanf(strtime, "%04u-%02u-%02u %02u:%02u:%02u",&sttm.tm_year, &sttm.tm_mon, &sttm.tm_mday, &sttm.tm_hour, &sttm.tm_min, &sttm.tm_sec );
    sttm.tm_year-=1900;
    sttm.tm_mon-=1;
    if((*ti = mktime(&sttm)) == -1) return -1;
    return 0;
}

int main( int argc, char** argv ) {
    char buf[50];
    time_t t,t2;
    t=time(0);
    printf("%ld\n\n",t);
    timetostr(t, buf, sizeof(buf));
    printf("数值转字符串\n");
    printf("%s\n", buf);
    printf("字符串转数值\n");
    strtotime(buf, sizeof(buf), &t2);
    printf("%ld\n",t2);
    return 0;
}