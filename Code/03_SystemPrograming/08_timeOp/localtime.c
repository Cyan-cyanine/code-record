#include <stdio.h>
#include <time.h>
 
int main(int argc,char *argv[])
{
  time_t tnow;
  tnow=time(0);      // 获取当前时间
  printf("tnow=%lu\n",tnow);   // 输出整数表示的时间
 
  struct tm *sttm; 
  sttm=localtime(&tnow);  // 把整数的时间转换为struct tm结构体的时间
 
  // yyyy-mm-dd hh24:mi:ss格式输出，此格式用得最多
  printf("%04u-%02u-%02u %02u:%02u:%02u\n",sttm->tm_year+1900,sttm->tm_mon+1,\
          sttm->tm_mday,sttm->tm_hour,sttm->tm_min,sttm->tm_sec);
 
  printf("%04u年%02u月%02u日%02u时%02u分%02u秒\n",sttm->tm_year+1900,\
          sttm->tm_mon+1,sttm->tm_mday,sttm->tm_hour,sttm->tm_min,sttm->tm_sec);
 
  // 只输出年月日
  printf("%04u-%02u-%02u\n",sttm->tm_year+1900,sttm->tm_mon+1,sttm->tm_mday);
}