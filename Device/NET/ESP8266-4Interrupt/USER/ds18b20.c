#include "config.h"
#include "ds18b20.h"
#include "delay.h"

/*单总线初始化时序*/
bit ds_init()
{
	bit i;
	DS = 1;
	_nop_();
	DS = 0;
	delay_us(75); //拉低总线499.45us 挂接在总线上的18B20将会全部被复位
	DS = 1; //释放总线
	delay_us(4); //延时37.95us 等待18B20发回存在信号
	i = DS;
	delay_us(20); //141.95us
	DS = 1;
	_nop_();
	return (i);
}

/*写一个字节*/
void write_byte(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		DS = 0;
		_nop_();//产生些时序
		DS = dat & 0x01;
		delay_us(10);//76.95us
		DS = 1; //释放总线准备下一次数据写入
		_nop_();
		dat >>= 1;
	}
}

uchar read_byte()
{
	uchar i, j, dat;
	for(i=0;i<8;i++)
	{
		DS = 0;
		_nop_();//产生读时序
		DS = 1;
		_nop_();//释放总线
		j = DS;
		delay_us(10);//76.95us
		DS = 1;
		_nop_();
		dat = (j<<7)|(dat>>1);	
	}
	return (dat);
}
void dsStart()
{
	ds_init();//初始化DS18B20
	write_byte(0xcc);//发送跳跃ROM指令
	write_byte(0x4e);//写暂存器指令
	write_byte(0x7f);//TH用户字节
	write_byte(0xf7);//TL用户字节
	write_byte(0x7f);//配置工作在12位模式下
	ds_init();//初始化DS18B20
	write_byte(0xcc);//发送跳跃ROM指令 
	write_byte(0x48);//拷贝暂存器到温度传感器的EEPROM中
}

float getTemperature()
{
	float temperature;
	uint i;
	uchar L, M;
	ds_init();//初始化DS18B20
	write_byte(0xcc);//发送跳跃ROM指令
	write_byte(0x44);//发送温度转换指令
	ds_init();//初始化DS18B20
	write_byte(0xcc);//发送跳跃ROM指令
	write_byte(0xbe);//读取DS18B20暂存器值
	L = read_byte();
	M = read_byte();
	//模拟显示-55度，实际测温需注解掉下面这两句
	//M = 0xfe;
	//L = 0x6f;

	i = M;
	i <<= 8;
	i |= L;		
	if(M >= 0x08)	//判断是否为负数
	{ 
		i = ~i + 1;//负数是以补码的形式存放的需要我们需要取反加1
	}
	temperature = i * 0.0625; //浮点型数据转换
	return temperature;
}