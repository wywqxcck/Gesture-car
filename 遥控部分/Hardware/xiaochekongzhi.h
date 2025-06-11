#ifndef __xiaochekongzhi_H
#define __xiaochekongzhi_H 	

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "OLED.h"
#include <string.h>
#include "TIME.h"
#include "mpu6050.h"
#include "NRF24L01.h"
 
void kongzhi_Init(void);
void xiaochekongzhi(void);
void yidongtubiao(void);
void chongzhi(void);
#endif
