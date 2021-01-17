#ifndef __DS18B20_H
#define __DS18B20_H

bit ds_init();

uchar read_byte();

void write_byte(uchar dat);

void dsStart();

float getTemperature();
#endif
