#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;
sbit led4=P1^3;
u8 dat;

void Init(void);//���ڳ�ʼ������
void Delay_ms(u16 n);//��ʱ�Ӻ���
void Sent_ZF(u8 dat);//����һ���ֽ�
void AT_Send_String(u8 *string);//�����ַ���
void ESP8266_Init();//ESP8266��ʼ��
void senddata();

void Init(void)		//���ڳ�ʼ������
{
 
	TMOD=0x20;	//��ʱ��������ʽ2,8λ�Զ�����(0010 0000)
	TL1=0xfd;		//װ���ֵ
	TH1=0xfd;		
	TR1=1;	//������ʱ��1
	REN=1;    //�����пڽ�������
	SM0=0;    //������ʽ1,10λ�첽�շ�
	SM1=1;   
	EA=1;   //��ȫ���жϿ���
	ES=1;     //�򿪴��п��ж�
}
/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void Delay_ms(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	Init();
	//P1=0Xff;
	ESP8266_Init();	//8266��ʼ��������ΪSTAģʽ������WiFi
	while(1){
		senddata();	//��������	
	}
}

 void Sent_ZF(u8 dat)  //����һ���ֽ�
{
	ES=0;	 //�رմ��п��ж�
	TI=0;	 //�رշ����жϱ�־λ
	SBUF=dat;
	while(!TI);
    TI=0;
    ES=1;	//�򿪴��п��ж�
}
void AT_Send_String(u8 *string)  //�����ַ���
{
  while(*string!='\0')
  {
    Sent_ZF(*string);
		//ÿ�η���һλ����
	string++;
	Delay_ms(1000);
  }

}
void ESP8266_Init()   //ESP8266��ʼ��
{	
	Delay_ms(1000);
	AT_Send_String("AT+RST\r\n");  //����ģ��
	Delay_ms(1000);
	AT_Send_String("AT+CWMODE=1\r\n");  //����STAģʽ
	Delay_ms(1000);
	AT_Send_String("AT+CIFSR\r\n");  //��ѯ����ip��ַ
	Delay_ms(1000);
	//AT_Send_String("AT+CWJAP=\"dingler_wifi\",\"dingler54321\"\r\n");  //����wifi
	AT_Send_String("AT+CWJAP=\"qingsong\",\"11111111\"\r\n");  //����wifi
	Delay_ms(1000);
	AT_Send_String("AT+CIPMUX=0\r\n");  //����Ϊ������ģʽ������ģ��
	Delay_ms(1000);
  

	
}


void senddata()
{
	AT_Send_String("AT+CIPSTART=\"TCP\",\"192.168.43.10\",8081\r\n"); //�����������ö˿�
  Delay_ms(1000);
	AT_Send_String("AT+CIPMODE=1\r\n"); //����͸��
  Delay_ms(1000);
	AT_Send_String("AT+CIPSEND\r\n"); //����͸��ģʽ
  Delay_ms(1000);
	AT_Send_String("OK"); //����OK
  Delay_ms(1000);
	AT_Send_String("qingsong\r\n"); //�����������ö˿�����
  Delay_ms(1000);
} 

void InterruptUART() interrupt 4  //����С�ƿ��� 
{ 
        RI=0;        //����
        dat= SBUF;    //�յ�������ռ�浽SBUF��
	  {
         if(dat=='o')
				 {
					 led4=0;    
				 }
		 if(dat=='f')  
				 {						 
				    led4=1; 
				 }
}
 }

