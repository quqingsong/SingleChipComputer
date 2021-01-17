#ifndef __CONFIG_H
#define __CONFIG_H
/****************************************************************
 通用头文件
****************************************************************/
#include <reg52.h>
#include <intrins.h>
#include <stdio.h>

#define uint unsigned int  
#define uchar unsigned char
#define ulong unsigned long

sbit DS  = P2^2;   //DS18B20单总线
sbit LED0 = P1^0;
sbit LED7 = P1^7;

#endif
