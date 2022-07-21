#ifndef _STUDENT_SYSTEM_H_
#define _STUDENT_SYSTEM_H_
#include <stdio.h>
#include <string.h> 
#include <strings.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#define elemType stu

typedef struct student{
    char num[8];       //学号
    char name[8];      //姓名
    int age;            //年龄
    int score;          //分数
}stu,*STU;

typedef struct StuNode{
    elemType Data;      //链表数据域
    struct StuNode *next;  //链表后继指针
    struct StuNode *prev;  //链表前驱指针
}stuNode,*STUNODE;

//--------[函数声明]--------↓
int studentSystem(char *fileName);
void stuInterface();                                    //显示学生系统界面
void browseStuInfo(STUNODE header);                     //浏览学生信息
void printList(STUNODE header);                         //打印学生信息
void addStuInfo(STUNODE header);                        //增加学生信息
void modifyStuInfo(STUNODE header);                     //修改学生信息
void deleteStuInfo(STUNODE header);                     //删除学生信息
void serchStuInfo(STUNODE header);                      //查找学生信息

//---------------------------------------[链表操作↓]
void swapStuStuNode(STUNODE i, STUNODE j);              //交换结点中的数据域
void subSort(STUNODE header,STUNODE low, STUNODE high, int userOption);//子排序
void quickSort(STUNODE header);                         //链表快速排序
STUNODE creatStuHeader();                               //创建表头,函数正常结束后返回一个表头结点
void deleteStuList(STUNODE header);                     //删除链表
STUNODE creatNewStuNode(elemType Data);                 //创建新节点，将新账户的信息传入到该结点后返回该结点
void insertStuNodeFromTail(STUNODE header,STUNODE specifiedStuNode);//将指定结点specifiedStuNode从链表尾部插入
STUNODE serchStuNode(STUNODE header,elemType Data);     //通过提供的数据Data匹配链表里对应的结点，找到后返回该结点地址
void deleteStuNode(STUNODE header,elemType Data);       //删除与Data匹配的结点
void readStuInfo(char *fileName,STUNODE header);        //读取文件信息到链表
void writeStuInfo(char *fileName,STUNODE header);       //将链表信息写入到文件内
//---------------------------------------------[自定义]
void cleanIo();                                         //清空缓冲区函数
void stopMoment();                                      //暂停,Press Enter to continu
void printTitle(char *title);                           //打印标题
bool getStrAndCheck(char *string,int maxSize);          //录入字符串并检查是否超出范围
bool getPassWord(char *string,int maxSize);             //录入用户密码
bool checkStuNum(char *string);

//--------[函数声明]--------↑

#endif