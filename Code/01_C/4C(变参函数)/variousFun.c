#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define SIZE 50

double sumup(const char *format, ...);

int main(void)
{
    short a = 1;
    float b = 1.2;
    char c = '\0';
    int d = 4;
    printf("%.2lf\n",sumup("#s#f#c#i",a,b,c,d));
    return 0;
}

double sumup(const char *format , ...)
{
    va_list p;
    va_start(p,format);
    double ans = 0;
    char arg[SIZE]={0}; //数组初始化为0
    int arg_num = 0;
    for(int i = 0;format[i];++i)
    {
        if(format[i] == '#')
        {
            arg[arg_num++] = format[i+1]; 
        }
    }
    for(int i =0;arg[i];++i)
    {
        switch(arg[i])
        {
            case 'i':
            case 's':
            case 'c':
                ans += va_arg(p,int);
                break;
            case 'f':
            case 'd':
                ans += va_arg(p,double);
                break;
            default:
                printf("format error!\n");
                break;
        }
    }
    return ans;
}