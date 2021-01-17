#include<reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;
sbit LED = P1^0;
u8 dat;
u8 returndata=0;
void Init(void);								//���ڳ�ʼ������
void delayms(u16 n);						//��ʱ�Ӻ���
void sendByte(u8 dat);					//����һ���ֽ�
void sendString(u8 *string);		//�����ַ���
void ESP8266_Init();						//ESP8266��ʼ��
void senddata();								//�����Ϣ
void Init(void)									//���ڳ�ʼ������
{
	TMOD = 0x20;									//��ʱ��������ʽ2,8λ�Զ�����(0010 0000)
	TL1 = 0xfd;										//װ���ֵ
	TH1 = 0xfd;		
	TR1 = 1;											//������ʱ��1
	REN=1;    										//�����пڽ�������
	SM0=0;    										//������ʽ1,10λ�첽�շ�
	SM1=1;   
	EA = 1;   										//��ȫ���жϿ���
	ES=1;     										//�򿪴��п��ж�
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

void sendByte(u8 dat)  					//����һ���ֽ�
{
	SBUF = dat;
	while(!TI);
    TI = 0;
       
	
}

void sendString(u8 *string)  		//�����ַ���
{
  while(*string)
  {
    sendByte(*string++);
		delayms(5);
  }

}
void ESP8266_Init()   					//esp8266��ʼ��
{
	sendString("AT\r\n"); 				//����ATָ��
	delayms(2000);
	sendString("AT+RST\r\n"); 		//����ģ��
	delayms(2000);
	sendString("AT+CWMODE=3\r\n"); //����ΪAPģʽ
	delayms(2000);
	//sendString("AT+CWJAP=\"dingler_wifi\",\"dingler54321\"\r\n");  //����wifi
	sendString("AT+CWJAP=\"qingsong\",\"11111111\"\r\n");  //����wifi
	delayms(2000);
  sendString("AT+CIFSR\r\n"); // �鿴ģ���ip��ַ
	delayms(2000);
  sendString("AT+CIPMODE=1\r\n"); //  ����ģ��͸��ģʽ
	delayms(2000);
  sendString("AT+CIPMUX=0\r\n");  //����Ϊ������ģʽ������ģ��
	delayms(2000);
  sendString("AT+CIPSTART=\"TCP\",\"192.168.6.10\",8080\r\n"); //�����������ö˿�
	delayms(2000);
}
void InterruptUART() interrupt 4   
{ 
        RI = 0;       				 			//����
        dat = SBUF;    							//�յ�������ռ�浽SBUF��
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

//�����Ϣ
void senddata()
{
	sendString("qingsong\r\n"); 		//�����������ö˿�����
	sendString(&returndata); 		
} 