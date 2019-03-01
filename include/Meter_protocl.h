#ifndef __METER_PROTOCL_H__
#define __METER_PROTOCL_H__

//��Ľṹ��һ���ǽṹ�嵫��Ҫ��֤λ��һ�£��ȷ���id��32λ���ٷ���״̬ 8λ
//����״̬
#define METER_ON     0B11111111
#define METER_OFF    0
#define METER_ERROR  0B01010101

typedef struct meter_message
{
    short id;         //id�� 32bit
    unsigned char status;    //״̬ 8bit ����  �� 11111111 �ر� 0 �쳣 01010101
    short year;
	char month;
	char day;
	char hour;
	char minute;
	char second;
}Meter_Message;

#endif
