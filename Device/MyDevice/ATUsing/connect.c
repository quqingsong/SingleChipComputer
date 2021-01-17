#include<reg52.h>				//51单片机常用的头文件
#define uchar unsigned char		//宏定义一个无符号的char类型
#define uint unsigned int		//宏定义一个无符号的int类型

//发送一字节
void sendByte(uchar b)
{
  SBUF = b;
  while(!TI);
  TI=0;
}

//发送字符串
void sendString(uchar *s)
{
  while(*s != '\0')	//字符串默认结尾'\0'，以此来判断字符串的结束
  {
    sendByte(*s);
    s++;
  }
}

//初始化ESP8266WiFi模块
void initEsp()
{
  uint a;
  SCON = 0x50;    //8位数据，可变波特率
  TMOD = 0x20;    //设置定时器1位16位自动重装模式
  TL1 = 0xfd;     //设置定时器初值，波特率为9600
  TH1 = 0xfd;
  ET1 = 0;        //禁止定时器1中断
  TR1 = 1;        //启动定时器1
  EA = 1;

  for (a=0; a<50000; a++);		//延时几秒，让模块有时间启动
  sendString("AT+CWMODE=1\n");	//设置为softAP和station共存模式

  //WiFi热点不能通过代码设置，可使用串口助手进行设置，该设置断电不丢失
  /*
  for (a=0; a<20000; a++);
  sendString("AT+CWSAP='TEST','12345678',1,3\n"); //建立WiFi热点
  */

  for (a=0; a<50000; a++);    
  sendString("AT+CIPMUX=1\n"); //启动多连接

  for (a=0; a<20000; a++);
  sendString("AT+CWJAP=\"qingsong\",\"11111111\"\r\n"); 
	
	for (a=0; a<20000; a++);
	sendString("AT+CIPSTART=\"TCP\",\"192.168.43.10\",8080\r\n"); //服务器的设置端口

  for (a=0; a<20000; a++);
  sendString("AT+CIPSTO=50\n");     //服务器超时时间设置

	for (a=0; a<20000; a++);
	sendString("AT+CIPSEND\r\n"); //进入透传模式
	for (a=0; a<20000; a++);
	sendString("OK"); //发送OK
  for (a=0; a<20000; a++);
	sendString("qingsong\r\n"); //服务器的设置端口数据
 
	
  RI=0;
  ES=1;   //初始化完成，串行口中断打开
}

//主函数  
void  main()  
{  
  initEsp();
}      
