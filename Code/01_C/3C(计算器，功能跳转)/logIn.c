#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50
#define Elemtype float


void print99() 
{
    int i, j;
    for (i = 1; i < 10; i++)
    {
        for (j = 1; j <= i; j++)
        {
            printf("%d*%d=%d\t", j, i, i * j);
        }
        putchar(10);
    }
}

Elemtype divi(Elemtype x, Elemtype y)
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
        return divi(x,y);
    default:
        printf("参数输入错误！\n");
        return 0;
    }
}

void cal()
{
    char s;
    char buf[SIZE];
    char num1[SIZE], num2[SIZE], sign;
    printf("请输入需要计算的公式:");
    scanf("%s", buf);
    getchar();
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
    printf("Press enter to continue……\n");
    getchar();
}

int main(void)
{
    char u_count[SIZE];
    char u_keyword[SIZE];
    int chance = 3;
    int choice;
    do
    {
        printf("请输入用户名:");
        scanf("%s", u_count);
        getchar(); //取出回车符
        printf("请输入密码:");
        scanf("%s", u_keyword);
        getchar(); //取出回车符
        if (!strcmp(u_keyword, "123456"))
        {
            printf("登陆成功!\n");
            do{
                printf("****************\n1:打印99乘法表\n2:计算器\n0:退出\n****************\n请输入选择");
                scanf("%d", &choice);getchar();
                switch (choice)
                {
                    case 0:
                        break;
                    case 1:
                        print99();
                        break;
                    case 2:
                        cal();
                        break;
                    default:
                        printf("参数输入错误，请重试！\n");
                        break;
                }
            }while(choice!=0);
            break;  //跳出第一个do,while
        }
        else{
            if(chance==1){
                printf("用户名或密码错误,稍后重试!\n");
                break;
            }
            printf("用户名或密码错误！还有%d次机会。\n", --chance);
        }
            
    } while (chance);
    printf("程序退出\n");
    return 0;
}