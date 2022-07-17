//注意：编码格式必须是GB2312
#include "font.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	Init_Font();		//初始化字库
	
	Clean_Area(0,0,800,480,0x00ffffff);				//清屏，白色背景
	char *str = "你好，世界";
	Display_characterX(100,100,str,0x00ff0000,1);	//显示字符串，红色字体
	Display_characterX(200,100,str,0x0000ff00,3);	//显示字符串，绿色字体
	Display_characterX(300,100,str,0x000000ff,5);	//显示字符串，蓝色字体
	Display_characterX(300,200,str,0x00ff0000,7);	//显示字符串，蓝色字体
	
	sleep(5);
	char count[10];
	int i;
	
	while(1)
	{
		Clean_Area(100,100,500,300,0x000000ff);				//清屏，蓝色背景
		sprintf(count, "%d", i++);
		Display_characterX(300,200,count,0x0000ff00,7);	//显示字符串，绿色字体
		sleep(1);
	}
	
	
	
	// Display_characterX(300,200,"你好",0x0000f800,7);	//显示字符串，蓝色字体
	
	UnInit_Font();		//关闭字库
}
