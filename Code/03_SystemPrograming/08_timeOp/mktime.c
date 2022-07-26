#include <stdio.h>
#include <string.h>
#include <time.h>

int main( int argc, char* argv[] ) {
    // 2019-12-25 15:05:03整数表示是1577257503
    struct tm sttm;
    memset( &sttm, 0, sizeof( sttm ) );

    sttm.tm_year  = 2019 - 1900;  // 注意，要减1900
    sttm.tm_mon   = 12 - 1;       // 注意，要减1
    sttm.tm_mday  = 25;
    sttm.tm_hour  = 15;
    sttm.tm_min   = 5;
    sttm.tm_sec   = 3;
    sttm.tm_isdst = 0;
    printf( "2019-12-25 15:05:03 is %lu\n", mktime( &sttm ) );

    //验证
    printf( "%04u-%02u-%02u %02u:%02u:%02u\n", sttm.tm_year + 1900, sttm.tm_mon + 1, sttm.tm_mday, sttm.tm_hour, sttm.tm_min, sttm.tm_sec );
    printf( "%04u年%02u月%02u日%02u时%02u分%02u秒\n", sttm.tm_year + 1900, sttm.tm_mon + 1, sttm.tm_mday, sttm.tm_hour, sttm.tm_min, sttm.tm_sec );
    printf( "%04u-%02u-%02u\n", sttm.tm_year + 1900, sttm.tm_mon + 1, sttm.tm_mday );
}