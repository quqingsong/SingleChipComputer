#include<reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;
sbit LED = P1^0;
u8 dat;
u8 returndata=0;
void Init(void);								//串口初始化函数
void delayms(u16 n);						//延时子函数
void sendByte(u8 dat);					//发送一个字节
void sendString(u8 *string);		//发送字符串
void ESP8266_Init();						//ESP8266初始化
void senddata();								//输出信息
void Init(void)									//串口初始化函数
{
	TMOD = 0x20;									//定时器工作方式2,8位自动重载(0010 0000)
	TL1 = 0xfd;										//装入初值
	TH1 = 0xfd;		
	TR1 = 1;											//启动定时器1
	REN=1;    										//允许串行口接收数据
	SM0=0;    										//工作方式1,10位异步收发
	SM1=1;   
	EA = 1;   										//打开全局中断控制
	ES=1;     										//打开串行口中断
}

void main()
{
    Init();
    ESP8266_Init();
    while(1){
			sendByte(returndata);
			senddata();
		}
}

void delayms(u16 n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<123;j++);
}

void sendByte(u8 dat)  					//发送一个字节
{
	SBUF = dat;
	while(!TI);
    TI = 0;
       
	
}

void sendString(u8 *string)  		//发送字符串
{
  while(*string)
  {
    sendByte(*string++);
		delayms(5);
  }

}
void ESP8266_Init()   					//esp8266初始化
{
	sendString("AT\r\n"); 				//测试AT指令
	delayms(2000);
	sendString("AT+RST\r\n"); 		//重启模块
	delayms(2000);
	sendString("AT+CWMODE=3\r\n"); //设置为AP模式
	delayms(2000);
	//sendString("AT+CWJAP=\"dingler_wifi\",\"dingler54321\"\r\n");  //连接wifi
	sendString("AT+CWJAP=\"qingsong\",\"11111111\"\r\n");  //连接wifi
	delayms(2000);
  sendString("AT+CIFSR\r\n"); // 查看模块的ip地址
	delayms(2000);
  sendString("AT+CIPMODE=1\r\n"); //  设置模块透传模式
	delayms(2000);
  sendString("AT+CIPMUX=0\r\n");  //设置为多连接模式，启动模块
	delayms(2000);
  sendString("AT+CIPSTART=\"TCP\",\"192.168.6.10\",8080\r\n"); //服务器的设置端口
	delayms(2000);
}
void InterruptUART() interrupt 4   
{ 
        RI = 0;       				 			//清零
        dat = SBUF;    							//收到的数据占存到SBUF中
	  {
         if(dat=='1')
				 {
					 LED =0;  
					 returndata=1;
				 }
				 if(dat=='0')  
				 {						 
				    LED =1; 
					 returndata=1;
				 }else{
					 returndata=0;
				 }					 
	  }
}

//输出信息
void senddata()
{
	sendString("qingsong\r\n"); 		//服务器的设置端口数据
	sendString(&returndata); 		
} 