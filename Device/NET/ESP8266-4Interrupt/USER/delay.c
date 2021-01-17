#include "config.h"
#include "delay.h"

void delay_ms(unsigned int i)
{
	unsigned int j,k;
	for(j=i;j>0;j--)
		for(k=118;k>0;k--);
}
/*us延时函数，执行一次US--所需6.5us进入一次函数需要11.95us*/
void delay_us(uchar us)
{
	while(us--);	
}