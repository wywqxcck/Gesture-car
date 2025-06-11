#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*中文字符字节宽度*/
#define OLED_CHN_CHAR_WIDTH			2		//UTF-8编码格式给3，GB2312编码格式给2

/*字模基本单元*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//汉字索引
	uint8_t Data[32];						//字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t OLED_CF16x16[];

/*图像数据声明*/
extern const uint8_t Diode[];
extern const uint8_t WEIXIAO[];
extern const uint8_t bukaixin[];
extern const uint8_t ling[];//数字零
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
/*按照上面的格式，在这个位置加入新的图像数据声明*/
//...

#endif


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
