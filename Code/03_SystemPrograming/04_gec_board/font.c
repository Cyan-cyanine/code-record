//ע�⣺�����ʽ������GB2312
#include "font.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	Init_Font();		//��ʼ���ֿ�
	
	Clean_Area(0,0,800,480,0x00ffffff);				//��������ɫ����
	char *str = "��ã�����";
	Display_characterX(100,100,str,0x00ff0000,1);	//��ʾ�ַ�������ɫ����
	Display_characterX(200,100,str,0x0000ff00,3);	//��ʾ�ַ�������ɫ����
	Display_characterX(300,100,str,0x000000ff,5);	//��ʾ�ַ�������ɫ����
	Display_characterX(300,200,str,0x00ff0000,7);	//��ʾ�ַ�������ɫ����
	
	sleep(5);
	char count[10];
	int i;
	
	while(1)
	{
		Clean_Area(100,100,500,300,0x000000ff);				//��������ɫ����
		sprintf(count, "%d", i++);
		Display_characterX(300,200,count,0x0000ff00,7);	//��ʾ�ַ�������ɫ����
		sleep(1);
	}
	
	
	
	// Display_characterX(300,200,"���",0x0000f800,7);	//��ʾ�ַ�������ɫ����
	
	UnInit_Font();		//�ر��ֿ�
}
