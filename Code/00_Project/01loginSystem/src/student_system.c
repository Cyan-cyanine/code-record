#include "student_system.h"

int studentSystem(char *fileName)
{
	STUNODE header = creatStuHeader();
	readStuInfo(fileName,header);
	while(1)
	{
		stuInterface(); //显示学生系统界面
        printf("请输入(0~5):");
        int userkey;
        scanf("%d",&userkey);
        cleanIo();
        switch(userkey)
        {
            case 1:
                browseStuInfo(header);
                break;
            case 2:
                addStuInfo(header);
                break;
            case 3:
                modifyStuInfo(header);
                break;
            case 4:
                deleteStuInfo(header);
                break;
            case 5:
                serchStuInfo(header);
                break;
            case 0:
                printf("退出成功,正在跳往主界面...\n");
                writeStuInfo(fileName,header);
                deleteStuList(header);
                sleep(1);
                return 0;
            default:
                break;
        }
    }
}

void stuInterface()//显示学生系统界面
{
	system("clear");
	printf("-------------[学生信息管理系统]-------------\n");
	printf("\t\t1.浏览信息\n");
	printf("\t\t2.增加信息\n");
	printf("\t\t3.修改信息\n");
	printf("\t\t4.删除信息\n");
	printf("\t\t5.查找信息\n");
	printf("\t\t0.保存退出\n");
	printf("--------------------------------------------\n");
}

void printList(STUNODE header)//打印链表
{
    STUNODE pos = header->next;
    printf("\t学号\t姓名\t年龄\t分数\n");
    if (pos != header)
    {
        while (pos != header)
        {
            printf("\t%s\t%s\t%d\t%d", pos->Data.num, pos->Data.name, pos->Data.age, pos->Data.score);
            pos = pos->next;
            putchar(10);
        }
        putchar(10);
    }
    else
    {
        printf("\n\t\t   空！\n\n");
    }
}

void browseStuInfo(STUNODE header)
{
    quickSort(header);  //排序选择,按学号/成绩排序
    printTitle("学生信息");
    printList(header);
    stopMoment();
}

void addStuInfo(STUNODE header)//增加结点
{
    printTitle("增加信息");
    stu tmpStuData;
    printList(header);
    int i;  //for循环变量
    while(1)
    {
        printf("学号:");
        if(getStrAndCheck(tmpStuData.num,sizeof(tmpStuData.num))!=true)
        {
            printf("学号需在%d位大小以内,请重新输入.\n",sizeof(tmpStuData.num)-1);
            continue;
        }
        if(!checkStuNum(tmpStuData.num))
        {
            printf("学号只能由数字组成,请重新输入.\n");
            continue;
        }
        if (serchStuNode(header, tmpStuData))
        {
            printf("学号%s已存在,请重新输入.\n", tmpStuData.num);
            continue;
        }
        break;
    }
    while(1)
    {
        printf("姓名:");
        if(getStrAndCheck(tmpStuData.name,sizeof(tmpStuData.name))!=true)
        {
            printf("姓名需在%d位字节大小以内,请重新输入.\n",sizeof(tmpStuData.name)-1);
            continue;
        }
        break;
    }
    while(1)
    {
        printf("年龄:");
        scanf("%d",&tmpStuData.age);
        cleanIo();
        if(tmpStuData.age<3||tmpStuData.age>30)
        {
            printf("年龄限制在3~30岁,请重新输入.\n");
            continue;
        }
        break;
    }
    while(1)
    {
        printf("分数:");
        scanf("%4d",&tmpStuData.score);
        cleanIo();
        if(tmpStuData.score<0||tmpStuData.score>1000)
        {
            printf("分数范围规定为0~1000,请重新输入.\n");
            continue;
        }
        break;
    }
        STUNODE newNode = creatNewStuNode(tmpStuData);
        insertStuNodeFromTail(header,newNode);
        printf("添加成功,");
        stopMoment();
}

void modifyStuInfo(STUNODE header)//修改结点
{
    printTitle("修改信息");
    stu tmpStuData;
    STUNODE posStuNode;
    printList(header);
    printf("请输入需要修改的学号:");
    getStrAndCheck(tmpStuData.num,sizeof(tmpStuData));
    posStuNode = serchStuNode(header, tmpStuData);
    if (posStuNode)
    {
        char userKey;
        printTitle("查询结果");
        printf("\t    姓名\t年龄\t分数\n");
        printf("\t    %s\t%d\t%d\n", posStuNode->Data.name, posStuNode->Data.age, posStuNode->Data.score);
        putchar(10);
        printf("注意:学号不可更改,确定修改该信息吗?(Enter for sure):");
        userKey=getchar();
        if(userKey!=10)
        {
            cleanIo();
            printf("不修改,正在跳转主界面.\n");
            sleep(1);
            return ;
        }
        while(1)
        {
            printf("新姓名:");
            if(getStrAndCheck(posStuNode->Data.name,sizeof(posStuNode->Data.name))!=true)
            {
                printf("姓名需在%d位字节大小以内,请重新输入.\n",sizeof(posStuNode->Data.name)-1);
                continue;
            }
            break;
        }
        while(1)
        {
            printf("年  龄:");
            scanf("%d",&posStuNode->Data.age);
            cleanIo();
            if(posStuNode->Data.age<3||posStuNode->Data.age>30)
            {
                printf("年龄限制在3~30岁,请重新输入.\n");
                continue;
            }
            break;
        }
        while(1)
        {
            printf("分  数:");
            scanf("%4d",&posStuNode->Data.score);
            cleanIo();
            if(posStuNode->Data.score<0||posStuNode->Data.score>1000)
            {
                printf("分数范围规定为0~1000,请重新输入.\n");
                continue;
            }
            break;
        }
        printf("修改成功,");
        stopMoment();
    }
    else
    {
        printf("未查到相关信息,");
        stopMoment();
        return ;
    }
}

void deleteStuInfo(STUNODE header)//删除结点
{
    printTitle("删除信息");
    printList(header);
    stu tmpStuData;
    STUNODE posStuNode;
    while(1)
    {
        printf("请输入要删除的学号:");
        if(getStrAndCheck(tmpStuData.num,sizeof(tmpStuData.num))!=true)
        {
            printf("学号需在%d位大小以内,请重新输入.\n",sizeof(tmpStuData.num)-1);
            continue;
        }
        if (!serchStuNode(header, tmpStuData))
        {
            printf("学号%s不存在,", tmpStuData.num);
            stopMoment();
            return ;
        }
        break;
    }
    posStuNode=serchStuNode(header,tmpStuData);
    if(posStuNode!=NULL)
    {
        char userKey;
        printTitle("查询结果");
        printf("\t    姓名\t年龄\t分数\n");
        printf("\t    %s\t%d\t%d\n", posStuNode->Data.name, posStuNode->Data.age, posStuNode->Data.score);
        putchar(10);
        printf("确定删除该信息吗?(Enter for sure):");
        userKey=getchar();
        if(userKey!=10)
        {
            cleanIo();
            printf("不删除,正在跳转主界面.\n");
            sleep(1);
            return ;
        }
        deleteStuNode(header,tmpStuData);
        printf("删除成功,正在跳转主界面.");
        sleep(1);
    }
    else{
        printf("未找到相关信息,");
        stopMoment();
        return ;
    }
}

void serchStuInfo(STUNODE header)//查找结点
{
    printTitle("查找信息");
    stu tmpStuData;
    STUNODE posStuNode;
    while(1)
    {
        printf("请输入要查找的学号:");
        if(getStrAndCheck(tmpStuData.num,sizeof(tmpStuData.num))!=true)
        {
            printf("学号需在%d位大小以内,请重新输入.\n",sizeof(tmpStuData.num)-1);
            continue;
        }
        posStuNode = serchStuNode(header,tmpStuData);
        if (!posStuNode)
        {
            printf("未查到相关信息,");
            stopMoment();
            return ;
        }
        else{
            printTitle("查询结果");
            printf("\t    姓名\t年龄\t分数\n");
            printf("\t    %s\t%d\t%d\n", posStuNode->Data.name, posStuNode->Data.age, posStuNode->Data.score);
            putchar(10);
            stopMoment();
        }
        break;
    }
}

//-----------------------------------------------------------------------

void swapStuNode(STUNODE i, STUNODE j)//交换结点中的数据域
{
    stu tmpStuData;
    tmpStuData = i->Data;
    i->Data = j->Data;
    j->Data = tmpStuData;
}

void subSort(STUNODE header,STUNODE low, STUNODE high, int userOption)//子排序
{
    if (low == header || low == high || high == header)
        return;
    STUNODE pivot = low;
    STUNODE i = low->next;
    STUNODE j = low->next;
    STUNODE iPre = low;
    while (j != high->next)
    {
        if (strcmp(pivot->Data.num, j->Data.num) > 0 && userOption == 1)
        {
            swapStuNode(i, j);
            iPre = i;
            i = i->next;
        }
        else if (pivot->Data.score < j->Data.score && userOption == 2)
        {
            swapStuNode(i, j);
            iPre = i;
            i = i->next;
        }
        j = j->next; //此处小细节，无论有没有if的操作，j都会进行后移
    }
    swapStuNode(low, iPre);
    subSort(header,low, iPre, userOption);
    subSort(header,i, high, userOption);
}

void quickSort(STUNODE header)//链表快速排序
{
    if (header->next == header)
        return;
    STUNODE low = header->next;
    STUNODE high = header->next;
    high = header->prev;
    int userOption;
    printTitle("排序选择");
    printf("\t     1.按学号排序\n");
    printf("\t     2.按分数排序\n");
    putchar(10);
    printf("请输入(1~2):");
    scanf("%1d", &userOption);
    cleanIo();
    subSort(header,low, high, userOption);
}

STUNODE creatStuHeader()  //创建表头,函数正常结束后返回一个表头结点
{
    STUNODE header= malloc(sizeof(stuNode));
    if(header==NULL)
    {
        perror("malloc stuNode failed.\n");
        return NULL;
    }
    header->next = header;
    header->prev = header;
    return header;
}

STUNODE creatNewStuNode(elemType Data)  //创建新节点，将新账户的信息传入到该结点后返回该结点
{
    STUNODE newNode = malloc(sizeof(stuNode));
    if(newNode==NULL)
    {
        perror("malloc newNode failed.\n");
        return NULL;
    }
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->Data = Data;
    return newNode;
}

void deleteStuList(STUNODE header)    //删除链表
{
    STUNODE pMove = header->prev;
    while(pMove->prev!=header)
    {
        pMove=pMove->prev;
        free(pMove->next);
    }
    header->next=header;
    header->prev=header;
    free(pMove);
}

void insertStuNodeFromTail(STUNODE header,STUNODE specifiedNode)   //将指定结点specifiedNode从链表尾部插入
{
    specifiedNode->next = header;
    specifiedNode->prev = header->prev;
    header->prev->next = specifiedNode;
    header->prev = specifiedNode;
}

STUNODE serchStuNode(STUNODE header,elemType Data)   //通过提供的数据Data匹配链表里对应的结点，找到后返回该结点地址
{
    STUNODE pMove = header->next;
    while(pMove!=header)
    {
        if(strcmp(pMove->Data.num,Data.num)==0)
            return pMove;
        pMove=pMove->next;
    }
        return NULL;
}

void deleteStuNode(STUNODE header,elemType Data)  //删除结点
{
    STUNODE posNode = serchStuNode(header,Data);
    posNode->prev->next = posNode->next;
    posNode->next->prev = posNode->prev;
    free(posNode);
}

void readStuInfo(char *fileName,STUNODE header) //读取文件信息到链表
{
    FILE *fp=fopen(fileName,"rb");
    if(fp==NULL)
        fp=fopen(fileName,"wb");
    elemType Data;
    STUNODE pMove = header->next;
    while(fread(&Data,sizeof(elemType),1,fp)==1)
    {
        STUNODE newNode = creatNewStuNode(Data);
        insertStuNodeFromTail(header,newNode);
        pMove=pMove->next;
    }
    fclose(fp);
}

void writeStuInfo(char *fileName,STUNODE header)   //将链表信息写入到文件内
{
    FILE *fp = fopen(fileName,"wb");
    STUNODE pMove = header->next;
    while(pMove!=header)
    {
        if(fwrite(&pMove->Data,sizeof(elemType),1,fp)!=1)
        {
            perror("write file error.\n");
            exit(0);
        }
        pMove=pMove->next;
    }
    fclose(fp);
}

void cleanIo()  //清空缓冲区函数
{
    while(getchar()!='\n');
}

void stopMoment()   //暂停
{
    printf("Press Enter to continue ...");
    cleanIo();
}

void printTitle(char *title)//打印标题
{
    system("clear");
    printf("--------------{ %s }----------------\n\n",title);
}

bool getStrAndCheck(char *string,int maxSize) //录入字符串并检查是否超出范围
{
    bzero(string,maxSize);
    char format[10];
    sprintf(format,"%%%ds",maxSize-1);    
    scanf(format,string);                                                       //让scanf最多录入maxSize-1个字符,防止字符数组被越界赋值,多余的字符会被cleanIo处理掉，
    cleanIo();
    if(string[maxSize-2]==0)                                                    //为数组的最后一位maxSize-1必需为0,不然会影响结构体物理结构的下一个成员,所以比较maxSize-1没有任何意义
        return true;
    else
        return false;
}

bool getPassWord(char *string,int maxSize)
{
    char *p=getpass("");
    strncpy(string,p,maxSize-1);
    if(string[maxSize-2]==0)                                                    
        return true;
    else
        return false;
}

bool checkStuNum(char *string)
{
    int i;
    for(i=0;i<strlen(string);i++)
    {
        if(string[i]<'0'||string[i]>'9')
            return false;
    }
    return true;
}