#include "stm32f10x.h"                  // Device header
#include "car.h"
#include "Delay.h"
#include "OLED.h"
#include "NRF24L01.h"
#include "DHT11.h"
#include "Serial.h"
#include "SG90.h"
#include "PWM.h"

extern int8_t wenshidu[4] ;
extern int8_t chary[9] ;
int8_t xuanze=0;
int8_t SG90_yaw=0,SG90_yroll_1=0,SG90_yroll_2=0;//舵机的三个轴
// 抓下 ，竖2 ， 左右， 竖1；

int main(void)
{   
	TIM1_PWM_Init();
	OLED_Init(); 
	PWM_Init();
	MotorAll_Init();	
	NRF24L01_Init();
	Serial1_Init();
	DHT11_GPIO_Config();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE );	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	 TIM1_PWM_Init();
	
	while (1)
	{	     
//////前进后退 根据手的姿态确定前进和后退移动速度		; 
//////左转右转 根据手的姿态确定左右转动速度	
		NRF24L01_GetRxBuf(chary);	
		xuanze = chary[0];
		switch(xuanze)
		{
//******************小车的移动	**************//			
			case 0:		yidong();
				break;

//******************机械臂控制**************//                                                                                         q
     	case 1:	
							if(chary[3]>1 || chary[3]<-1 || chary[3]==0)
							{
								SG90_yaw=(3*chary[3]+90);//底						
							}
							if(chary[4]>1 || chary[4]<-1 || chary[4]==0)
							{
								SG90_yroll_1=(1.5*chary[4]+90);//主机
								SG90_yroll_2=(1.5*chary[4]+90);//副机
							}

							if(chary[5]>7) //抓取
							{
									TIM_SetCompare1(TIM1, angle_to_pulse(170));
							}
							if(chary[5]<-7) //抓取
							{
									TIM_SetCompare1(TIM1, angle_to_pulse(60));
							}										
							Set_Servos_Angles(SG90_yroll_2,SG90_yaw,SG90_yroll_1); // PA8, PA9（副）, PA10, PA11（主）
				break; 

//*****************温湿度的反馈*************//					
			case 2:		huanjing();
				break;		
		}
	}	
}

