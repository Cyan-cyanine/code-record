#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//编写一个通用函数，获取操作系统的时间
/* 常用的时间格式
 yyyy-mm-dd hh24:mi:ss
 yyyymmddhh24miss
 yyyy-mm-dd
 yyyymmdd
 hh24:mi:ss    //24代表24小时制
 hh24miss
 hh24:mi
 hh24mi
 hh24
 mi
 */
void LocalTime( char* out_stime, const char* in_fmt, const int in_interval ) {

}