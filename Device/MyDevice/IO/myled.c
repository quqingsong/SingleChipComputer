#include "reg52.h"			 
#include <intrins.h>
typedef unsigned int u16;	 
typedef unsigned char u8;
sbit LED = P1^0; 


void UsartInit()
{
	SCON=0X50;			
	TMOD=0X20;			
//	PCON=0X80;		
	TH1=0XFD;				
	TL1=0XFD;
	ES=1;				
	EA=1;			
	TR1=1;			
	TI = 0;	
}

/*******************************************************************************/

void main()
{	
	UsartInit();  
	//EA=1;						
	while(1);		
}


void Usart() interrupt 4
{
	char receiveData;

	receiveData=SBUF;
	RI = 0;
	
		if(receiveData=='>'){
	    LED=0;
			SBUF='#';
			while(!TI);		   
			TI=0;			       
			SBUF='o';
			while(!TI);		   
			TI=0;			      
			SBUF='n';
			while(!TI);		 
			TI=0;			       
			SBUF='\n';
			while(!TI);		   
			TI=0;			     
	}
		if(receiveData =='<'){
	    LED=1;
			SBUF='#';
			while(!TI);		  
			TI=0;			
			SBUF='o';
			while(!TI);	
			TI=0;			
			SBUF='f';
			while(!TI);	
			TI=0;		
			SBUF='f';
			while(!TI);	
			TI=0;		
			SBUF='\n';
			while(!TI);	
			TI=0;		

	}
}