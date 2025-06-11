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


float Pitch,Roll,Yaw;			//�������ڴ�Ÿ������ݵı���
float xpitch=0,xroll=0,xyaw=0; //�������ǰ��ֵ
float ypitch,yroll,yyaw; //����ֵ����Ϊ�������ݣ�
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
	OLED_Init();		//OLED��ʼ��	
	OLED_ShowString(0,0,"MPU6050",OLED_8X16);
	OLED_Update();
	
	IIC_Init();	
	MPU6050_initialize(); 	
	DMP_Init();	
	
	TIM2_Getsample_Int(1999,719);		
	Key_Init();
	LED_Init ();
}

//******************��������******************//
void chongzhi()
{
					xpitch = Pitch;
					xroll = Roll ;
					xyaw = Yaw+15;	
}
//******************С������****************//
void xiaochekongzhi(void)
{
				uint8_t string[10] = {0};
				yroll = Roll-xroll;// �Դﵽ����λ�õ�����
				yyaw = Yaw+15-xyaw; // �ѵ�������λ�õ�����
				ypitch = Pitch-xpitch; //�Ѵﵽ����λ�õ�����
//��������
				KeyNum = Key_GetNum();
				if (KeyNum==1)
				{
					chongzhi();
					LED1_ON();
					WENSHIDU_P=1;
				}
				else{LED1_OFF ();}			
//*****************ģʽ�л�******************//
		if(Pitch<-30) //����۷��л�
		{
			delay_s(500);
			if(Pitch>-25)
			{
				P++;	
				if(P>2) //���ֵ��ת
				{	P=0;}	}	}	
		if(Pitch>30)
		{
			delay_s(500);
			if(Pitch<25)
			{
				P--;	
				if(P<0) //���ֵ��ת
				{	P=2;}	}	}		
		if(P==0) //�ٴ�ΪС�������ƶ��ṩ���� (��˵����ô�㣬�ǵ�ʱ������Ҳ��Ҫһ������)
		{
			o=0;
		}
		
}		

//********************�ƶ�ͼ��****************//
void yidongtubiao()
{
	//��ֹ
	if(round(-yroll)<10 &&  round(-yroll)>-10 && round(yyaw)<10 && round(yyaw)>-10)
	{
			OLED_Clear ();
      OLED_ShowImage(0,0,127,63,shizitubiao);
			OLED_Update();
	}
	if(round(-yroll)>10) //����
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
	if(round(-yroll)<-10) //����
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
	if(round(yyaw)<-15) //����
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
	if(round(yyaw)>15) //����
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
