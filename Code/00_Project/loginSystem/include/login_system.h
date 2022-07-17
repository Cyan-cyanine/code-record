#ifndef _LOGIN_SYSTEM_H_
#define _LOGIN_SYSTEM_H_
#include "student_system.h"
#define ElemType account

typedef struct account{
    char userName[8];   //用户名
    char passWord[20];  //密码
    char phoneNum[12];  //电话号码
    char accountFileName[12];//账户信息文件名
}account,*ACCOUNT;

typedef struct Node{
    ElemType Data;//账户结构体
    struct Node *next;  //链表后继指针
    struct Node *prev;  //链表前驱指针
}node,*NODE;

//--------[函数声明]--------↓
void loginSystem();                                 //登录系统主函数
void loginInterface();                              //显示登陆界面菜单
void signUp(NODE header);                           //注册账号
void logIn(NODE header);                            //登录账号
void logOut(NODE header);                           //注销账号
void browseAccount(NODE header);                    //浏览账户信息
int userNameCheck(NODE header, account tmpAccount); //用户名合法检查,包含除字母和数字以外的字符返回-2,存在同名返回-1
char *matchAccount(NODE header,ElemType tmpAccount);//账户信息匹配,成功返回true,失败返回false
//bool getStrAndCheck(char *string,int maxSize);      //录入字符串并检查是否超出范围
//---------------------------------------[链表操作↓]
NODE creatHeadOfList();                             //创建表头,函数正常结束后返回一个表头结点
void deleteList(NODE header);                       //删除链表
NODE creatNewNode(ElemType Data);                   //创建新节点，将新账户的信息传入到该结点后返回该结点
void insertNodeFromTail(NODE header,NODE specifiedNode);//将指定结点specifiedNode从链表尾部插入
void deleteNode(NODE header,ElemType Data);         //删除与Data匹配的结点
NODE serchNode(NODE header,ElemType Data);          //通过提供的数据Data匹配链表里对应的结点，找到后返回该结点地址
void readInfoFromFile(char *fileName,NODE header);  //读取文件信息到链表
void writeInfoToFile(char *fileName,NODE header);   //将链表信息写入到文件内
//--------------------------------[清空缓冲区和暂停↓]
//void cleanIo();                                     //清空缓冲区函数
//void stopMoment();                                  //暂停,Press Enter to continu
//void printTitle(char *title);                       //打印标题
//--------[函数声明]--------↑
#endif