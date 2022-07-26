#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>   // 注意，不是time.h
 
int main()
{
  struct timeval begin,end;  // 定义用于存放开始和结束的时间
 
  gettimeofday(&begin,0);    // 计时器开始
  printf("begin time(0)=%ld,tv_sec=%ld,tv_usec=%ld\n",time(0),begin.tv_sec,begin.tv_usec);
 
  sleep(2);
  usleep(100000);     // 程序睡眠十分之一秒(100ms)。
 
  gettimeofday(&end,0);      // 计时器结束
  printf("end   time(0)=%ld,tv_sec=%ld,tv_usec=%ld\n",time(0),end.tv_sec,end.tv_usec);
 
  printf("计时过去了%ld微秒。\n",\
         (end.tv_sec-begin.tv_sec)*1000000+(end.tv_usec-begin.tv_usec));
}