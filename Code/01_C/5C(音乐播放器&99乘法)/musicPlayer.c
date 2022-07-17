#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define ElemType char

typedef struct Node
{
    ElemType Data[50];
    struct Node *next;
} mr, *MR;

void menu();
void addMusic(MR header);
void browsMusic(MR header);
MR creatHeader(); //创建表头
MR creatNode(ElemType *Data);
MR serchNode(MR header, ElemType *Data);
void insertMusicFromTail(MR header, ElemType *Data);
bool getStrAndCheck(char *string, int maxSize); //录入字符串并检查是否超出范围
void stopMoment();                              //暂停
void cleanIo();                                 //清空缓冲区函数
void printTitle(char *title);                   //打印标题
void playMusic(MR header);
void deleteList(MR header);
MR serchMusic(MR header, int num);
void addMulMusic(MR header);

int main(void)
{
    MR header = creatHeader();
    int userKey;
    while (1)
    {
        menu();
        printf("请输入(0~2):");
        scanf("%5d", &userKey);
        cleanIo();
        switch (userKey)
        {
        case 1:
            playMusic(header);
            break;
        case 2:
            addMusic(header);
            break;
        case 3:
            addMulMusic(header);
            break;
        case 4:
            browsMusic(header);
            break;
        case 0:
            deleteList(header);
            free(header);
            return 0;
        default:
            break;
        }
    }

    return 0;
}
void menu()
{
    system("clear");
    printf("--------------------------------------------\n");
    printf("\t\t1.播放音乐\n");
    printf("\t\t2.导入单曲\n");
    printf("\t\t3.批量导入歌曲\n");
    printf("\t\t4.查看音乐库\n");
    printf("\t\t0.退出\n");
    printf("--------------------------------------------\n");
}

void playMusic(MR header)
{
    MR curMusic = header->next;
    int musicNum = 1;
    char userKey;
    while (1)
    {
        system("clear");
        printTitle("音乐播放器");
        if(curMusic==header)
        {
            printf("歌曲库为空,请添加后再播放.\n");
            stopMoment();
            return ;
        }
        printf("\t       <%s>\n", curMusic->Data);
        printf("\n上一首(a) 下一首(s) 退出(q):");
        scanf("%c", &userKey);
        cleanIo();
        switch (userKey)
        {
        case 'a':
            if(musicNum==1)
                while(curMusic->next!=header)
                {
                    curMusic=curMusic->next;
                    musicNum++;
                }
            else
            {
                curMusic=serchMusic(header,--musicNum);
            }
            break;
        case 's':
            if(curMusic->next==header)
            {
                curMusic=curMusic->next->next;
                musicNum=1;
            }
            else{
                curMusic=curMusic->next;
                musicNum++;
            }
            break;
        case 'q':
            printf("确定要退出吗(Enter for sure)?");
            userKey=getchar();
            if (userKey == 10)
                return;
            else
                break;
        default :
            break;
        }
    }
}

void addMusic(MR header)
{
    MR tmpNode;
    char musicName[sizeof(tmpNode->Data)];
    while (1)
    {
        printf("请输入歌名:");
        if (getStrAndCheck(musicName, sizeof(musicName)) != true)
        {
            printf("歌名长度超过限制,请输入%d位内的歌名.\n", sizeof(musicName) - 1);
            continue;
        }
        tmpNode = serchNode(header, musicName);
        if (tmpNode != NULL)
        {
            printf("歌名已存在.\n");
            continue;
        }
        insertMusicFromTail(header, musicName);
        printf("添加成功,");
        stopMoment();
        break;
    }
}

void addMulMusic(MR header)
{
    MR tmpNode;
    int musicNum=1;
    char musicName[sizeof(tmpNode->Data)];
    printTitle("歌曲导入");
    printf("\"Enter:确认 q!:退出:\"\n");
    while (1)
    {
        printf("歌曲%d:",musicNum);
        if (getStrAndCheck(musicName, sizeof(musicName)) != true)
        {
            printf("歌名长度超过限制,请输入%d位内的歌名.\n", sizeof(musicName) - 1);
            continue;
        }
        if(musicName[0]=='q'&&musicName[1]=='!')
            return ;
        tmpNode = serchNode(header, musicName);
        if (tmpNode != NULL)
        {
            printf("歌名已存在.\n");
            continue;
        }
        insertMusicFromTail(header, musicName);
        musicNum++;
    }
}

void browsMusic(MR header)
{
    system("clear");
    int num = 1;
    printTitle("歌曲信息");
    MR pMove = header->next;
    if (pMove == header)
    {
        printf("尚未存储任何信息.\n\n");
        stopMoment();
        return;
    }
    while (pMove != header)
    {
        printf("\t    %d.\"%s\"\n", num++, pMove->Data);
        pMove = pMove->next;
    }
    putchar(10);
    stopMoment();
}

MR creatHeader() //创建表头
{
    MR header = malloc(sizeof(mr));
    if (header == NULL)
    {
        perror("malloc header failed.\n");
        return NULL;
    }
    header->next = header;
    return header;
}

MR creatNode(ElemType *Data)
{
    MR newNode = malloc(sizeof(mr));
    if (newNode == NULL)
    {
        perror("malloc newNode failed.\n");
        return NULL;
    }
    strcpy(newNode->Data, Data);
    newNode->next = NULL;
    return newNode;
}

MR serchNode(MR header, ElemType *Data)
{
    MR pMove = header;
    while (pMove->next != header)
    {
        if (strcmp(Data, pMove->next->Data) == 0)
            break;
        pMove = pMove->next;
    }
    if (pMove->next == header)
        return NULL;
    else
        return pMove;
}

MR serchMusic(MR header, int num)
{
    MR pMove = header->next;
    while (--num)
        pMove = pMove->next;
    return pMove;
}

void deleteList(MR header)
{
    if(header->next==header)
        return ;
    MR pMove_pre = header;
    MR pMove = header->next;
    while (pMove != header)
    {
        pMove_pre = pMove_pre->next;
        pMove = pMove->next;
        free(pMove_pre);
    }
    header->next = header;
}

void insertMusicFromTail(MR header, ElemType *Data)
{
    MR newNode = creatNode(Data);
    MR pMove = header->next;
    while (pMove->next != header)
        pMove = pMove->next;
    newNode->next = header;
    pMove->next = newNode;
}

bool getStrAndCheck(char *string, int maxSize) //录入字符串并检查是否超出范围
{
    bzero(string, maxSize);
    char format[10];
    sprintf(format, "%%%ds", maxSize - 1);
    scanf(format, string); //让scanf最多录入maxSize-1个字符,防止字符数组被越界赋值,多余的字符会被cleanIo处理掉，
    cleanIo();
    if (string[maxSize - 2] == 0) //为数组的最后一位maxSize-1必需为0,不然会影响结构体物理结构的下一个成员,所以比较maxSize-1没有任何意义
        return true;
    else
        return false;
}

void cleanIo() //清空缓冲区函数
{
    while (getchar() != '\n')
        ;
}

void stopMoment() //暂停
{
    printf("Press Enter to continue ...");
    cleanIo();
}

void printTitle(char *title) //打印标题
{
    system("clear");
    printf("--------------{ %s }----------------\n\n", title);
}