#include "config.h"
#include "esp8266.h"
#include "delay.h"

uint canSend = 0; //可以发送数据标志位
unsigned char code str[][60]={
	{"AT+RST\r\n"},
	{"AT+CWMODE=1\r\n"},
	{"AT+CWMODE=2\r\n"},
	{"AT+CWMODE=3\r\n"},
	{"AT+CWJAP_DEF=\"Tenda_F90CF8\",\"1q2w3e4r5t233,.\"\r\n"},
	{"AT+CIPMUX=1\r\n"},
	{"AT+CIPSERVER=1,8080\r\n"},
	{"AT+CIPSTART=\"TCP\",\"192.168.0.101\",5678\r\n"},
	{"AT+CIPSEND=22\r\n"},
	{"AT+CIPCLOSE\r\n"}
};

//mode: 1:STA  2:AP  3:AP+STA
void esp8266_init(char mode)
{
	char i=0;
	if(mode==1)
	{
			TI = 1;//因为使用printf()或puts()前都应软件置位TI = 1；
			printf(str[1]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
			
			TI = 1;
			printf(str[4]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
	}
	else if(mode==2)
	{
			TI = 1;
			printf(str[2]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
			
			TI = 1;
			printf(str[5]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
			
			TI = 1;
			printf(str[6]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
	}
	else if(mode==3)
	{
		TI = 1;
		printf(str[3]);
		while(!TI);
		TI = 0;
		delay_ms(1000);
		
		TI = 1;
		printf(str[4]);
		while(!TI);
		TI = 0;
		delay_ms(1000);
		
		//暂时搞不懂 这里 循环多次手机壳已连接但不能发送数据 不循环的话可以发送数据但手机又不可以连接
		for(i=0;i<4;i++)
		{
			TI = 1;
			printf(str[5]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
			
			TI = 1;
			printf(str[6]);
			while(!TI);
			TI = 0;
			delay_ms(1000);
		}
		
//		TI = 1;
//		printf(str[5]);
//		while(!TI);
//		TI = 0;
//		delay_ms(1000);
//		
//		TI = 1;
//		printf(str[6]);
//		while(!TI);
//		TI = 0;
//		delay_ms(1000);
	}
	canSend = 1;
}
void sendJavaSocket(float val)
{
	//测试连接TCP服务器并发送数据start
	TI = 1;
	printf(str[9]);
	while(!TI);
	TI = 0;
	delay_ms(20);
	
	TI = 1;
	printf(str[7]);
	while(!TI);
	TI = 0;
	delay_ms(20);
	
	TI = 1;
	printf(str[8]);
	while(!TI);
	TI = 0;
	delay_ms(20);
	
	TI = 1;
	printf("采集到温度为：%.3f℃\n",val);
	while(!TI);
	TI = 0;
	delay_ms(50);

	TI = 1;
	printf(str[9]);
	while(!TI);
	TI = 0;
	delay_ms(20);
	//测试连接TCP服务器并发送数据end
}

uint canSendSatus()
{
	if(canSend)
		return 1;
	else 
		return 0;
}

