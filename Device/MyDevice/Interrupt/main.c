#include<reg52.h>
 
typedef unsigned char uchar;

sbit led0=P1^0;
 
void Serial_comInit()
{
	SCON=0X50;			//设置为工作方式1 ,既然是方式一，自然要确定波特率，设置定时器1
	TMOD=0X20;//8位重装载
	PCON=0X80;
	TH1=0xFD;//波特率9600
	TL1=0XFD;
	ES=1;						//打开通信中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}
 
void main(void)
{
	Serial_comInit();
	while(1);
}
 
void communication() interrupt 4
{
	uchar receiveData;
	receiveData=SBUF;//出去,接,收到的数据
	RI = 0;//清除接收中断标志位
	//SBUF=receiveData;//将接收到的数据放入到发送寄存器
	
	led0=receiveData;
	
	while(!TI);			 //等待发送数据完成
	TI=0;						 //清除发送完成标志位
}