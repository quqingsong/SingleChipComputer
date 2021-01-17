 
#include<reg52.h>
 
#define uchar unsigned char
 
#define uint  unsigned int
uchar buf;
 
#define led P1
 
void main(void)
 
{
 
SCON=0x50;//�趨���ڹ�����ʽ0101 0000
 
PCON=0x00;
 
TMOD=0x20;
 
EA=1;
 
ES=1;
 
TL1=0xfd;//������9600
 
TH1=0xfd;
 
TR1=1;
 
while(1);
 
}
 
 
 
//�����жϷ�����
 
void serial() interrupt 4
 
	{
 
	ES=0;		//��ʱ�رմ����ж�
 
	RI=0;
 
	buf=SBUF;	//���յ�����Ϣ��SBUF�ŵ�buf�С�
 
	switch(buf)
 
	{
 //��Ӧasill��
	case 0x31: led=0xfe;break;   //������ 0011 0001  ʮ���� 49 �����ַ� 1  16���� 0X31
 
	case 0x32: led=0xfd;break;	 //1111 1101
 
	case 0x33: led=0xfb;break;
 
	case 0x34: led=0xf7;break;
 
	case 0x35: led=0xef;break;   
 
	case 0x36: led=0xdf;break;	
 
	case 0x37: led=0xbf;break;
 
	case 0x38: led=0x7f;break;
 
	}
 
	ES=1;		//���¿��������ж�
 
	SBUF=buf;
	//������ڷ�����TI=0����������TI=1;while(!TI)	�ȴ�������ɡ�
	while(!TI);
	TI=0;
 
}