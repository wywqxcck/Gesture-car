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


float Pitch,Roll,Yaw;			//定义用于存放各个数据的变量
float xpitch=0,xroll=0,xyaw=0; //储存更新前的值
float ypitch,yroll,yyaw; //区间值（作为最终数据）
int16_t P=0;
extern uint16_t o;
extern int8_t wenshidu[1];
int8_t WENSHIDU_P=0;


uint8_t KeyNum;

void kongzhi_Init(void)
{
	delay_init();
	uart_init(115200);
	NRF24L01_Init();
	OLED_Init();		//OLED初始化	
	OLED_ShowString(0,0,"MPU6050",OLED_8X16);
	OLED_Update();
	
	IIC_Init();	
	MPU6050_initialize(); 	
	DMP_Init();	
	
	TIM2_Getsample_Int(1999,719);		
	Key_Init();
	LED_Init ();
}

//******************按键重置******************//
void chongzhi()
{
					xpitch = Pitch;
					xroll = Roll ;
					xyaw = Yaw+15;	
}
//******************小车控制****************//
void xiaochekongzhi(void)
{
				uint8_t string[10] = {0};
				yroll = Roll-xroll;// 以达到重置位置的作用
				yyaw = Yaw+15-xyaw; // 已到达重置位置的作用
				ypitch = Pitch-xpitch; //已达到重置位置的作用
//按键重置
				KeyNum = Key_GetNum();
				if (KeyNum==1)
				{
					chongzhi();
					LED1_ON();
					WENSHIDU_P=1;
				}
				else{LED1_OFF ();}			
//*****************模式切换******************//
		if(Pitch<-30) //横滚折返切换
		{
			delay_s(500);
			if(Pitch>-25)
			{
				P++;	
				if(P>2) //最大值反转
				{	P=0;}	}	}	
		if(Pitch>30)
		{
			delay_s(500);
			if(Pitch<25)
			{
				P--;	
				if(P<0) //最大值反转
				{	P=2;}	}	}		
		if(P==0) //再次为小车结束移动提供条件 (话说，这么搞，那到时候舵机不也需要一个？？)
		{
			o=0;
		}
		
}		

//********************移动图标****************//
void yidongtubiao()
{
	//静止
	if(round(-yroll)<10 &&  round(-yroll)>-10 && round(yyaw)<10 && round(yyaw)>-10)
	{
			OLED_Clear ();
      OLED_ShowImage(0,0,127,63,shizitubiao);
			OLED_Update();
	}
	if(round(-yroll)>10) //向上
	{
			OLED_Clear();	OLED_ShowImage(0,0,127,63,shang1);delay_ms(3);OLED_Update();
		if(round(-yroll)>2)
		{
			OLED_Clear();	OLED_ShowImage(0,0,127,63,shang2);delay_ms(2);OLED_Update();	
			if(round(-yroll)>30)
			{
			OLED_Clear();	OLED_ShowImage(0,0,127,63,shang3);delay_ms(1);OLED_Update();					
			}	
		}
	}
	if(round(-yroll)<-10) //向下
	{
			OLED_Clear();	OLED_ShowImage(0,0,127,63,xia1);delay_ms(3);OLED_Update();
		if(round(-yroll)<-20)
		{
			OLED_Clear();	OLED_ShowImage(0,0,127,63,xia2);delay_ms(2);OLED_Update();
			if(round(-yroll)<-30)		
			{
			OLED_Clear();	OLED_ShowImage(0,0,127,63,xia3);delay_ms(1);OLED_Update();				
			}				
		}
	}
	if(round(yyaw)<-15) //向右
	{
			OLED_Clear();OLED_ShowImage(0,0,127,63,you1);delay_ms(3);OLED_Update();
		if(round(yyaw)<-20)
		{
			OLED_Clear();OLED_ShowImage(0,0,127,63,you2);delay_ms(2);OLED_Update();		
			if(round(yyaw)<-25)	
			{
			OLED_Clear();OLED_ShowImage(0,0,127,63,you3);delay_ms(1);OLED_Update();				
			}				
		}
	}
	if(round(yyaw)>15) //向左
	{
			OLED_Clear ();OLED_ShowImage(0,0,127,63,zuo1);delay_ms(3);OLED_Update();
		if(round(yyaw)>20)
		{
			OLED_Clear ();OLED_ShowImage(0,0,127,63,zuo2);delay_ms(2);OLED_Update();	
			if(round(yyaw)>25)
			{
			OLED_Clear ();OLED_ShowImage(0,0,127,63,zuo3);delay_ms(1);OLED_Update();
			}				
		}
	}
}
