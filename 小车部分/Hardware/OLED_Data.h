#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*�����ַ��ֽڿ��*/
#define OLED_CHN_CHAR_WIDTH			2		//UTF-8�����ʽ��3��GB2312�����ʽ��2

/*��ģ������Ԫ*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//��������
	uint8_t Data[32];						//��ģ����
} ChineseCell_t;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];

/*ͼ����������*/
extern const uint8_t Diode[];
extern const uint8_t WEIXIAO[];
extern const uint8_t bukaixin[];
extern const uint8_t ling[];//������
extern const uint8_t yi[];
extern const uint8_t er[];
extern const uint8_t san[];
extern const uint8_t si[];
extern const uint8_t wu[];
extern const uint8_t liu[];
extern const uint8_t qi[];
extern const uint8_t ba[];
extern const uint8_t jiu[];
extern const uint8_t yiban1[];
extern const uint8_t zonghe[11][108];
extern const uint8_t zhangchuang[];
/*��������ĸ�ʽ�������λ�ü����µ�ͼ����������*/
//...

#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
