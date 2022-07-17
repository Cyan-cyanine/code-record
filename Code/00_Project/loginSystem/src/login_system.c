#include "login_system.h"

#define ACCOUNT_INFO "account"

void loginSystem()  //登录系统主函数
{
    NODE header = creatHeadOfList();    //创建表头结点,用于记录注册账户的信息,账户信息以双向循环链表形式存储
    int userKey;    //用于存储用户的选择
    readInfoFromFile(ACCOUNT_INFO,header);
    while (1)
    {
        loginInterface();   //显示登陆界面菜单
        printf("请输入(0~4):");
        scanf("%3d", &userKey);
        cleanIo();
        switch (userKey)
        {
            case 1:
                signUp(header);
                break;
            case 2:
                logIn(header);
                break;
            case 3:
                logOut(header);
                break;
            case 4:
                browseAccount(header);
                break;
            case 0:
                printf("退出登录系统...\n");
                writeInfoToFile(ACCOUNT_INFO,header);
                deleteList(header);
                stopMoment();
                return ;
            default:
                break;
        }
    }
}

void loginInterface() //显示登陆界面菜单
{
    system("clear");
    printf("-----------{ 登录系统主界面 }-------------\n\n");
    printf("              [1.注册账户]\n");
    printf("              [2.登录账户]\n");
    printf("              [3.注销账户]\n");
    printf("              [4.查看账户]\n");
    printf("              [0.保存退出]\n");
    printf("\n------------------------------------------\n");
}

void signUp(NODE header) //注册账号
{
    system("clear");
    account tmpAccount; //创建临时账户结构体并初始化，用于记录用户传进的数据
    printTitle("账号注册");
    while (1)
    {
        printf("注册手机号:");
        scanf("%s",tmpAccount.phoneNum);
        cleanIo();
        int i; //用于记录循环次数
        for (i = 0; tmpAccount.phoneNum[i] >= '0' && tmpAccount.phoneNum[i] <= '9'; i++); 
        if (i != 11)
        {
            printf("输入有误,请输入正确的手机号.\n");
            continue;
        }
        while (1)
        {
            printf("用户名:");
            if(getStrAndCheck(tmpAccount.userName,sizeof(tmpAccount.userName))!=true)
            {
                printf("用户名需在%d位数内,请重新输入.\n",sizeof(tmpAccount.userName)-1);
                continue;
            }
            if (userNameCheck(header,tmpAccount) != 0)
            {
                if (userNameCheck(header,tmpAccount) == -1)
                    printf("用户名已存在,请重试.\n");
                else if(userNameCheck(header,tmpAccount) == -2)
                    printf("用户名只能包含字母和数字,请重新输入.\n");
                continue;
            }
            while (1)
            {
                printf("密  码:");
                if(getStrAndCheck(tmpAccount.passWord,sizeof(tmpAccount.passWord))!=true)
                {
                    printf("密码需在%d位内,请重新输入.\n",sizeof(tmpAccount.passWord)-1);
                    continue;
                }
                char passWordCheck[sizeof(tmpAccount.passWord)];
                printf("确认密码:");
                if(getStrAndCheck(tmpAccount.passWord,sizeof(tmpAccount.passWord))!=true)
                {
                    printf("两次密码不一致,请重新输入.\n");
                    continue;
                }
                system("clear");
                printTitle("注册成功");
                strcpy(tmpAccount.accountFileName,tmpAccount.userName);
                NODE newNode = creatNewNode(tmpAccount);
                insertNodeFromTail(header, newNode);
                printf("\t  手机号:\t%s\n\t  用户名:\t%s\n\t  密  码:\t%s\n\n", newNode->Data.phoneNum, newNode->Data.userName, newNode->Data.passWord);
                stopMoment();
                return;
            }
        }
    }
}

void logIn(NODE header) //登录账号
{
    account tmpAccount;
    char *fileName=matchAccount(header,tmpAccount);
    if(fileName!=NULL)
    { 
        strcpy(tmpAccount.accountFileName,fileName);
        studentSystem(tmpAccount.accountFileName);
        return ;
    }
    else
        return ;
}

void logOut(NODE header) //注销账号
{
    system("clear");
    account tmpAccount;
    printTitle("注销账户");
    printf("注销用户名:");
    getStrAndCheck(tmpAccount.userName,sizeof(tmpAccount.userName));
    printf("密码(不回显):");
    getPassWord(tmpAccount.passWord,sizeof(tmpAccount.passWord));
    NODE tmpNode=serchNode(header, tmpAccount);
    if ( tmpNode!= NULL)
    {
        char userkey;
        printTitle("用户信息");
        printf("\t用户名:\t%s\n\t密  码:\t%s\n", tmpAccount.userName, tmpAccount.passWord);
        printf("\n删除后学生系统保留的信息也将被清空!\n确定删除该用户吗(press Enter for true):");
        userkey=getchar();
        if (userkey == 10)
        {
            char *shellOrder="rm ";
            char format[strlen(shellOrder)+strlen(tmpNode->Data.accountFileName)+1];
            sprintf(format,"rm %s",tmpNode->Data.accountFileName);
            system(format);
            deleteNode(header, tmpAccount);
            printf("删除成功,");
            stopMoment();
            return;
        }
        else
        {
            cleanIo();
            printf("取消删除,正在跳转到主界面...\n");
            sleep(2);
            return;
        }
    }
    else
    {
        printf("未查找到该用户或用户密码错误...\n");
        printf("Press Enter to continue...\n");
        getchar();
        return;
    }
}

void browseAccount(NODE header) //浏览账户信息
{
    // char magPassword[10] = {0};
    // printf("管理员密码:");
    // getPassWord(magPassword,sizeof(magPassword));
    // if (strcmp(magPassword, "carry") != 0)
    // {
    //     printf("密码错误,请联系管理员.\n");
    //     sleep(1);
    //     return;
    // }
    system("clear");
    printTitle("账户信息");
    NODE pMove = header->next;
    if(pMove==header)
    {
        printf("尚未存储任何信息.\n");
        stopMoment();
        return ;
    }
    printf("用户名\t密码\t\t手机号\t\t文件名\n");
    while (pMove != header)
    {
        printf("%s\t%s\t\t%s\t%s\n", pMove->Data.userName, pMove->Data.passWord, pMove->Data.phoneNum,pMove->Data.accountFileName);
        pMove = pMove->next;
    }
    printf("\nPress Enter to continue...\n");
    getchar();
}

int userNameCheck(NODE header, account tmpAccount) //用户名合法检查
{
    for (int i = 0; tmpAccount.userName[i]; i++)
    {
        if (tmpAccount.userName[i] >= '0' && tmpAccount.userName[i] <= '9' || tmpAccount.userName[i] >= 'a' && tmpAccount.userName[i] <= 'z' || tmpAccount.userName[i] >= 'A' && tmpAccount.userName[i] <= 'Z')
            continue;
        else
            return -2;
    }
    if (serchNode(header, tmpAccount) != NULL)
        return -1;
    return 0;
}

char *matchAccount(NODE header,ElemType tmpAccount)//账户信息匹配,成功返回true,失败返回false
{
    int loginNum=3;
    while(1)
    {
        printf("登录用户名:");
        if(getStrAndCheck(tmpAccount.userName,sizeof(tmpAccount.userName))!=true)
        {
            printf("用户名需在%d位数内,请重新输入.\n",sizeof(tmpAccount.userName)-1);
            continue;
        }
        if(userNameCheck(header,tmpAccount) != 0)
        {
            if(userNameCheck(header,tmpAccount) == -2)
            {
                printf("用户名只能包含字母和数字,请重新输入.\n");
                continue;
            }
        }
        printf("密码(不回显):");
        if(getPassWord(tmpAccount.passWord,sizeof(tmpAccount.passWord))!=true)
        {
            printf("密码需在%d位内,请重新输入.\n",sizeof(tmpAccount.passWord)-1);
            continue;
        }
        NODE tmpNode = serchNode(header,tmpAccount);
        if (tmpNode!= NULL)
        {
            printf("登录成功,正在跳转...\n");
            sleep(1);
            return tmpNode->Data.accountFileName;
        }
        else
        {
            if (!--loginNum)
            {
                printf("账号或密码错误,请稍后再试.\n");
                stopMoment();
                return NULL;
            }
            printf("账号或密码不正确,您还有%d次输入机会...\n", loginNum);
            continue;
        }
    }
}

NODE creatHeadOfList()  //创建表头,函数正常结束后返回一个表头结点
{
    NODE header= malloc(sizeof(node));
    if(header==NULL)
    {
        perror("malloc node failed.\n");
        return NULL;
    }
    header->next = header;
    header->prev = header;
    return header;
}

void deleteList(NODE header)    //删除链表
{
    NODE pMove = header->prev;
    while(pMove->prev!=header)
    {
        pMove=pMove->prev;
        free(pMove->next);
    }
    header->next=header;
    header->prev=header;
    free(pMove);
}

NODE creatNewNode(ElemType Data)  //创建新节点，将新账户的信息传入到该结点后返回该结点
{
    NODE newNode = malloc(sizeof(node));
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

void insertNodeFromTail(NODE header,NODE specifiedNode)   //将指定结点specifiedNode从链表尾部插入
{
    specifiedNode->next = header;
    specifiedNode->prev = header->prev;
    header->prev->next = specifiedNode;
    header->prev = specifiedNode;
}

void deleteNode(NODE header,ElemType Data)  //删除结点
{
    NODE posNode = serchNode(header,Data);
    posNode->prev->next = posNode->next;
    posNode->next->prev = posNode->prev;
    posNode->next=NULL;
    posNode->prev=NULL;
    free(posNode);
}

NODE serchNode(NODE header,ElemType Data)   //通过提供的数据Data匹配链表里对应的结点，找到后返回该结点地址
{
    NODE pMove = header->next;
    while(pMove!=header)
    {
        if(strcmp(pMove->Data.userName,Data.userName)==0)
            return pMove;
        pMove=pMove->next;
    }
        return NULL;
}

void readInfoFromFile(char *fileName,NODE header) //读取文件信息到链表
{
    FILE *fp=fopen(fileName,"rb");
    if(fp==NULL)
        fp=fopen(fileName,"wb");
    ElemType Data;
    NODE pMove = header->next;
    while(fread(&Data,sizeof(ElemType),1,fp)==1)
    {
        NODE newNode = creatNewNode(Data);
        insertNodeFromTail(header,newNode);
        pMove=pMove->next;
    }
    fclose(fp);
}

void writeInfoToFile(char *fileName,NODE header)   //将链表信息写入到文件内
{
    FILE *fp = fopen(fileName,"wb");
    NODE pMove = header->next;
    while(pMove!=header)
    {
        if(fwrite(&pMove->Data,sizeof(ElemType),1,fp)!=1)
        {
            perror("write file error.\n");
            exit(0);
        }
        pMove=pMove->next;
    }
    fclose(fp);
}
