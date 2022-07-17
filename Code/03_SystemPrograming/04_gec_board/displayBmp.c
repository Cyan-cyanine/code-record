#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int displayBmp(char *picName, int setx, int sety) {
    int lcdFd = open("/dev/fd0", O_RDWR);  //打开lcd文件
    if (lcdFd == -1) {
        printf("open lcd error.\n");
        return -1;
    }
    struct fb_var_screeninfo var;             //定义可变参数结构体var
    ioctl(lcdFd, FBIOGET_VSCREENINFO, &var);  //将lcd的屏幕参数存入到var
    int lcd_w = var.xres;  //获取屏幕宽度,单位：字节
    int lcd_h = var.yres;  //获取屏幕高度,单位：字节
    int lcd_size = lcd_h * lcd_w *
                   (var.bits_per_pixel / 8);  //整块屏幕的字节数大小,单位：字节
    char lcdBuf[lcd_size];                    //定义lcdBuf
    int *lcdmem = mmap(NULL, lcd_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                       lcdFd, 0);  // lcd内存映射
    //------------------------------------[第一部分↑]-------------------------------------
    // 1.打开lcd
    // 2.获取lcd的长，宽,单位为像素
    // 3.计算lcdj总字节数(用于申请lcd缓冲和共享内存),计算方法：长*宽*每像素所占位数/8
    // 4.申请共享内存(mmap)
    // tips:lcd缓冲区用于像素对齐(RGB->ARGB)，共享内存用于显示图片

    int bmpFd = open(picName, O_RDWR);
    if (bmpFd == -1) {
        printf("open %s error.\n", picName);
        return -1;
    }
    char bmpHeadInfo[54];  //用于存放bmp头文件信息
    read(bmpFd, bmpHeadInfo, 54);
    // int bmp_w = bmpHeadInfo[18] | bmpHeadInfo[19] <<8 |bmpHeadInfo[20] << 16
    // | bmpHeadInfo[21] << 24; int bmp_h = bmpHeadInfo[22] | bmpHeadInfo[23]
    // <<8 |bmpHeadInfo[24] << 16 | bmpHeadInfo[25] << 24; int bmp_bit =
    // bmpHeadInfo[28] | bmpHeadInfo[29] << 8;
    // 获取图片位数,用于定义bmpBuf的大小
    int bmp_bit, bmp_byte, bmp_w, bmp_h;
    memcpy(&bmp_w, bmpHeadInfo + 18, 4);  //获取图片宽度,单位：像素
    memcpy(&bmp_h, bmpHeadInfo + 22, 4);  //获取图片高度,单位：像素
    bmp_byte = bmp_bit / 8;
    int bmp_complete = (4 - bmp_w * bmp_byte % 4) % 4;  // bmp行补齐的字节数
    int bmp_line = bmp_w * bmp_byte +
                   bmp_complete;  // bmp行字节数 = 实际行字节数 + 补齐字节数
    char bmpBuf[bmp_line * bmp_h];  //定义bmpBuf
    //------------------------------------[第二部分↑]-------------------------------------
    // 1.打开bmp
    // 2.获取bmp的位数，长，宽(bmp_bit,bmp_w,bmp_h)
    // 3.计算每个像素所占字节数(bmp_byte)
    // 4.计算行补齐字节数(bmp_complete)
    // 5.计算行字节数(bmp_line)
    // 6.定义bmpbuf

    int x, y;
    for (y = 0; y < lcd_h && y < bmp_h; y++) {
        for (x = 0; x < lcd_w && x < bmp_w; x++) {
            lcdBuf[0 + var.bits_per_pixel / 8 * (x + y * lcd_w)] =
                bmpBuf[0 + bmp_byte * (x + (bmp_h - 1 - y) * bmp_w)];
            lcdBuf[1 + var.bits_per_pixel / 8 * (x + y * lcd_w)] =
                bmpBuf[1 + bmp_byte * (x + (bmp_h - 1 - y) * bmp_w)];
            lcdBuf[2 + var.bits_per_pixel / 8 * (x + y * lcd_w)] =
                bmpBuf[2 + bmp_byte * (x + (bmp_h - 1 - y) * bmp_w)];
            lcdBuf[3 + var.bits_per_pixel / 8 * (x + y * lcd_w)] = 0;  //透明度
        }
    }
    //------------------------------------[第三部分↑]-------------------------------------
    // RGB->ARGB，bmpBuf转到lcdBuf，并垂直翻转

    int draw_w = bmp_w < lcd_w - setx ? bmp_w : lcd_w - setx;
    int draw_h = bmp_h < lcd_h - sety ? bmp_h : lcd_h - sety;
    for (y = 0; y < bmp_h; y++) {
        memcpy(lcdmem + setx + (sety + y) * lcd_w,
               &lcdBuf[var.bits_per_pixel / 8 * lcd_w * y],
               draw_w * var.bits_per_pixel / 8);
    }
    //------------------------------------[第四部分↑]-------------------------------------
    // 将lcdBuf的内容输出到屏幕上，如果图片超出显示范围，则截除超出范围的像素点
    munmap(lcdmem, lcd_size);
    close(lcdFd);
    close(bmpFd);
    //------------------------------------[第五部分↑]-------------------------------------
    //关闭所有文件并释放共享内存
    return 0;
}
