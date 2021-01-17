#include"reg52.h"


typedef unsigned char u8;
typedef unsigned int u16;

sbit led=P1^0;
sbit led2=P2^0;

//中断初始化函数
void init(){
	//IE寄存器，EA为总中断，ES为串口中断。
	EA=1;
	ES=1;
	
	//工作方式寄存器
	TMOD=0x20;              //采用方式二	8位自动重装定时器/计数器
	//计算T0的初值,9600
	TH1=0xF9;
	TL1=0xF9;
	//与串行口相关
	PCON=0x80;
	//打开定时器
	TR1=1;
	//SCON串行口控制寄存器
	SCON=0x50;
}

//主函数
void main(){
	init();
	while(1);
	
}

void USAR() interrupt 4{
	//SBUF是输出缓冲器，会产生溢出。 
	u8 receiveData=SBUF;
	
	led=receiveData;
	led2=receiveData;
	//软件清零
	RI=0;
	//将接收到的数据放入到发送寄存器
	SBUF=receiveData;
	//等待发送数据完成
	while(!TI);
	//清除发送完成标志位
	TI=0;
	
}