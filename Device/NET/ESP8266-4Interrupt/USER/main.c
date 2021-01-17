#include "config.h"
#include "uart.h"
#include "esp8266.h"
#include "ds18b20.h"
#include "delay.h"

unsigned char mSec;
uchar dat[10],cnt = 0,flag = 0;

//数码管显示手机发送过来的数据 手机连接的是ESP8266的wifi 
sbit du = P2^6;
sbit wei = P2^7;
													//"0" //"1"  //"2"  //"3"  //"4"  //"5"  //"6"  //"7"
unsigned code leds[8] = {0x7F,  0xBF,  0xDF,  0xEF,  0xF7,  0xFB,  0xFD,  0xFE};
														//"0"  //"1" //"2" //"3" //"4" //"5" //"6" //"7" //"8" //"9" //"A" //"B" //"C" //"D" //"E" //"F" //"H" //"L" //"-" //熄灭
unsigned code numbers[20] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x76, 0x38, 0x40, 0x00};

//串口中断函数
void interruptUart() interrupt 4 {
	if(RI == 1) {//接受完成标志
		RI = 0;//要软件清0
		dat[cnt] = SBUF;//将数据赋给num SBUF位内部寄存器 num = SBUF表示接受SBUF = num表示发送	
		if(dat[0]=='+')
			cnt++;
		else
			cnt=0;
		if(cnt==10)
		{
			cnt=0;
			flag = dat[9]-0x30;
		}
	}
}
//定时器0中断函数
void timer0() interrupt 1 {
		//从新给初值
		TH0 = (65535- 46082) / 256;//高八位
		TL0 = (65535- 46082) % 256;//低八位
		mSec ++;
		if (mSec == 200) {//10s时间到
			mSec = 0;
			if (canSendSatus()) 
			{
				//P1 = ~P1;
				sendJavaSocket(getTemperature());//发送数据到java上位机
			}
		}
}

void main() {
	dsStart();
	initUart();
	esp8266_init(3);
	timer0Init();//定时器0初始化
	while(1) {
		
		if((flag>=0)&&(flag<=9))
		{
			
			du = 1;
			P0 = numbers[flag];
			du = 0;
			wei = 1;
			P0 = 0xFE;
			wei = 0;
			
			switch(flag)
			{
				case 0:	P1=leds[flag];
				break;
				case 1:	P1=leds[flag];
				break;
				case 2:	P1=leds[flag];
				break;
				case 3:	P1=leds[flag];
				break;
				case 4:	P1=leds[flag];
				break;
				case 5:	P1=leds[flag];
				break;
				case 6:	P1=leds[flag];
				break;
				case 7:	P1=leds[flag];
				break;
				case 8:	P1=leds[3];delay_ms(500);P1=leds[4];delay_ms(500);
				break;
				case 9:	P1=leds[6];delay_ms(500);P1=leds[7];delay_ms(500);
				break;
				default:
				break;
			}
		 }
	}
}