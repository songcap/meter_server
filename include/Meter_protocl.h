#ifndef __METER_PROTOCL_H__
#define __METER_PROTOCL_H__

//表的结构不一定是结构体但是要保证位数一致，先发送id（32位）再发送状态 8位
//电表的状态
#define METER_ON     0B11111111
#define METER_OFF    0
#define METER_ERROR  0B01010101

typedef struct meter_message
{
    short id;         //id号 32bit
    unsigned char status;    //状态 8bit 长度  打开 11111111 关闭 0 异常 01010101
    short year;
	char month;
	char day;
	char hour;
	char minute;
	char second;
}Meter_Message;

#endif
