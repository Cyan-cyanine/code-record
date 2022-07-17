#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 30
#define Elemtype float

Elemtype Divid(Elemtype x, Elemtype y)
{
    return x / y;
}

Elemtype mul(Elemtype x, Elemtype y)
{
    return x * y;
}

Elemtype sub(Elemtype x, Elemtype y)
{
    return x - y;
}

Elemtype add(Elemtype x, Elemtype y)
{
    return x + y;
}

Elemtype calculator(Elemtype x, char sign, Elemtype y){
    switch (sign)
    {
    case '+':
        return add(x,y);
    case '-':
        return sub(x,y);
    case '*':
        return mul(x,y);
    case '/':
        return Divid(x,y);
    default:
        printf("参数输入错误！\n");
        break;
    }
}

int main(void)
{
    char buf[SIZE];
    char num1[SIZE], num2[SIZE], sign;
    fscanf(stdin, "%s", buf);
    for (int i = 0; buf[i]; i++) //分离数据
    {
        if (buf[i]=='+'||buf[i]=='-'||buf[i]=='*'||buf[i]=='/') //判断加减乘除
        {
            int j,k;
            num1[i] = 0;
            sign = buf[i];
            for (j = i + 1, k = 0; buf[j]; j++, k++)
                num2[k] = buf[j];
            num2[k]=0;
            break;
        }
        num1[i] = buf[i];
    }
    printf("结果:%.2f\n",calculator(atof(num1), sign, atof(num2)));
    return 0;
}