 
#include<reg52.h>
 
#define uchar unsigned char
 
#define uint  unsigned int
uchar buf;
 
#define led P1
 
void main(void)
 
{
 
SCON=0x50;//设定串口工作方式0101 0000
 
PCON=0x00;
 
TMOD=0x20;
 
EA=1;
 
ES=1;
 
TL1=0xfd;//波特率9600
 
TH1=0xfd;
 
TR1=1;
 
while(1);
 
}
 
 
 
//串行中断服务函数
 
void serial() interrupt 4
 
	{
 
	ES=0;		//暂时关闭串口中断
 
	RI=0;
 
	buf=SBUF;	//把收到的信息从SBUF放到buf中。
 
	switch(buf)
 
	{
 //对应asill表
	case 0x31: led=0xfe;break;   //二进制 0011 0001  十进制 49 控制字符 1  16进制 0X31
 
	case 0x32: led=0xfd;break;	 //1111 1101
 
	case 0x33: led=0xfb;break;
 
	case 0x34: led=0xf7;break;
 
	case 0x35: led=0xef;break;   
 
	case 0x36: led=0xdf;break;	
 
	case 0x37: led=0xbf;break;
 
	case 0x38: led=0x7f;break;
 
	}
 
	ES=1;		//重新开启串口中断
 
	SBUF=buf;
	//如果还在发送中TI=0。不发送中TI=1;while(!TI)	等待发送完成。
	while(!TI);
	TI=0;
 
}