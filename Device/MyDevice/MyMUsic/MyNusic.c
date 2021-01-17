#include <reg51.h>
#include <stdio.h>
sbit beep = P2^3;
unsigned char timer0h, timer0l, time;

//延时函数
void delayled(unsigned int n)
{
    unsigned int i=0,j=0;
    for(i=0;i<n;i++){
        for(j=0;j<10;j++);
		}
}

//led灯
void led(){
	int i=0;
	for(i;i<8;i++){
		P1=0x01<<i;
		delayled(20);
	}
}

code unsigned char high[] = {
    0xF8, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC,//低音1234567
    0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE,//中音1234567 
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF,//高音1234567
};
code unsigned char low[] = {
    0x8C, 0x56, 0x22, 0x64, 0x04, 0x90, 0x0C,//低音1234567
    0x44, 0xAA, 0x08, 0x32, 0x82, 0xC8, 0x06,//中音1234567
    0x22, 0x56, 0x84, 0x9A, 0xC0, 0xE4, 0x02,//高音1234567
};
code unsigned char music[] = {
   5,2,1,3,2,1,5,2,1,3,2,1,5,2,1,3,2,1,1,2,2,
   2,2,1,4,2,1,3,2,1,2,2,1,5,2,2,
   5,2,1,3,2,1,5,2,1,3,2,1,5,2,1,3,2,1,1,2,2,
   2,2,1,4,2,1,3,2,1,2,2,1,1,2,3,
   2,2,1,2,2,1,4,2,1,4,2,1,3,2,1,3,2,1,2,2,1,5,2,2,
   2,2,1,4,2,1,3,2,1,2,2,1,5,2,2,
   5,2,1,3,2,1,5,2,1,3,2,1,5,2,1,3,2,1,1,2,2,
   2,2,1,4,2,1,3,2,1,2,2,1,1,2,3,
   0,0,0,
   };//《我是一个粉刷匠》可更改此处代码播放不同歌曲
void t0int() interrupt 1 //T0中断程序，控制发音的音调
{
TR0 = 0; //先关闭T0
beep = !beep; //输出方波, 发音
TH0 = timer0h; //下次的中断时间, 这个时间, 控制音调高低
TL0 = timer0l;
TR0 = 1; //启动T0
}
void delay(unsigned char time) //延时程序，控制发音的时间长度
{
unsigned char i;
unsigned long j;
for(i = 0; i < time; i++) //双重循环, 共延时t个半拍
for(j = 0; j < 5000; j++); //延时期间, 可进入T0中断去发音
TR0 = 0; //关闭T0, 停止发音
}
void song() //演奏一个音符
{
TH0 = timer0h; //控制音调
TL0 = timer0l;
TR0 = 1; //启动T0, 由T0输出方波去发音
delay(time); //控制时间长度
}
void main(void)
{
unsigned char k, i;
TMOD = 0x01; //置T0定时工作方式1
ET0 = 1; //开T0中断
EA = 1; 
while(1) {
i = 0;
time = 1;
while(time) {
k = music[i] + 7 * music[i + 1] - 1;
//第i个是音符, 第i+1个是第几个八度
timer0h = high[k]; 
timer0l = low[k]; 
time = music[i + 2]; 
i += 3;
song(); //发出一个音符
led();
}
}
}