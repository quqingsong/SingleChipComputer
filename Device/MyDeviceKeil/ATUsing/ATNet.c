#include<reg52.h>
#include<stdio.h>
 
#define uchar unsigned char 
#define uint unsigned int
 
void delayms(uint x)   //51单片机的常用延时方式
{
	uint i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}
 
void uart_init()      //串口的初始化
{
	TMOD = 0x20;
	TH1 = 0XFd;
	TL1 = 0XFd;
	SCON = 0x50;
	PCON = 0X00;
	TR1 = 1;
	EA = 1;
	ES = 1;
} 
 
void wifi_init()      //初始化wifi模块
{
	ES = 0;       //关闭串口中断，以免发送指令过程中被其他事情打断
	TI = 1;
 
	printf("AT+RST\r\n");  //往串口发重启指令，在单片机中使用printf默认是往串口发送数据
	delayms(1200);         //适当延时，给wifi模块一点反应时间
 
	printf("AT+CWMODE=1\r\n");  //选择STA模式
	delayms(1200);
 
	printf("AT+CIPMUX=0\r\n");  //单通道模式
	delayms(1200);
	
	printf("AT+CIPSTART=\"TCP\",\"192.168.43.10\",8080\r\n");  //设置远程主机IP和端口号
	delayms(1200);
 
	printf("AT+CIPMODE=1\r\n");  //选择透传
	delayms(1200);
 
	printf("AT+CIPSEND\r\n");  //发送数据命令
	delayms(1200);
 
	while(!TI);
	TI = 0;  
	ES = 1;  //重新开启串口中断
}
 
void send(char *p)  //发送数据函数
{
	TI=0;
	do
	{	
		SBUF = *p;
		p++;
		while(!TI);
		TI = 0;
	}while(*p);
	SBUF = ' ';
	while(!TI);
	TI = 0;
}
 
 
void main()
{
	uart_init();
	wifi_init();
	while(1)
	{
		send("qingsong\r\n");  //这里只简单发送几个字符串作为演示
		delayms(1000);  //适当延时
	}
}