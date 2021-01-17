#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;
sbit led4=P1^3;
u8 dat;

void Init(void);//串口初始化函数
void Delay_ms(u16 n);//延时子函数
void Sent_ZF(u8 dat);//发送一个字节
void AT_Send_String(u8 *string);//发送字符串
void ESP8266_Init();//ESP8266初始化
void senddata();

void Init(void)		//串口初始化函数
{
 
	TMOD=0x20;	//定时器工作方式2,8位自动重载(0010 0000)
	TL1=0xfd;		//装入初值
	TH1=0xfd;		
	TR1=1;	//启动定时器1
	REN=1;    //允许串行口接收数据
	SM0=0;    //工作方式1,10位异步收发
	SM1=1;   
	EA=1;   //打开全局中断控制
	ES=1;     //打开串行口中断
}
/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void Delay_ms(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	Init();
	//P1=0Xff;
	ESP8266_Init();	//8266初始化，设置为STA模式，连接WiFi
	while(1){
		senddata();	//发送数据	
	}
}

 void Sent_ZF(u8 dat)  //发送一个字节
{
	//ES=0;	 //关闭串行口中断
	//TI=0;	 //关闭发送中断标志位
	SBUF=dat;
	while(!TI);
    TI=0;
    //ES=1;	//打开串行口中断
}
void AT_Send_String(u8 *string)  //发送字符串
{
  while(*string!='\0')
  {
    Sent_ZF(*string);
		//每次发送一位数据
	string++;
	Delay_ms(1000);
  }

}
void ESP8266_Init()   //ESP8266初始化
{	
	Delay_ms(1000);
	AT_Send_String("AT+RST\r\n");  //重启模块
	Delay_ms(1000);
	AT_Send_String("AT+CWMODE=1\r\n");  //设置STA模式
	Delay_ms(1000);
	AT_Send_String("AT+CIFSR\r\n");  //查询本地ip地址
	Delay_ms(1000);
	//AT_Send_String("AT+CWJAP=\"dingler_wifi\",\"dingler54321\"\r\n");  //连接wifi
	AT_Send_String("AT+CWJAP=\"qingsong\",\"11111111\"\r\n");  //连接wifi
	Delay_ms(1000);
	AT_Send_String("AT+CIPMUX=0\r\n");  //设置为单连接模式，启动模块
	Delay_ms(1000);
}


void senddata()
{
	AT_Send_String("AT+CIPMODE=1\r\n"); //开启透传
  Delay_ms(1000);
	AT_Send_String("AT+CIPSTART=\"TCP\",\"192.168.43.10\",8080\r\n"); //服务器的设置端口
  Delay_ms(100000);
	AT_Send_String("AT+CIPSEND\r\n"); //进入透传模式
  Delay_ms(1000);
	AT_Send_String("OK"); //发送OK
  Delay_ms(1000);
	AT_Send_String("qingsong\r\n"); //服务器的设置端口数据
  Delay_ms(1000);
} 

void InterruptUART() interrupt 4  //控制小灯开关 
{ 
        RI=0;        //清零
        dat= SBUF;    //收到的数据占存到SBUF中
	  {
         if(dat=='1')
				 {
					 led4=0;    
				 }
		 if(dat=='0')  
				 {						 
				    led4=1; 
				 }
}
 }