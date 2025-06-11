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
int8_t SG90_yaw=0,SG90_yroll_1=0,SG90_yroll_2=0;//�����������
// ץ�� ����2 �� ���ң� ��1��

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
//////ǰ������ �����ֵ���̬ȷ��ǰ���ͺ����ƶ��ٶ�		; 
//////��ת��ת �����ֵ���̬ȷ������ת���ٶ�	
		NRF24L01_GetRxBuf(chary);	
		xuanze = chary[0];
		switch(xuanze)
		{
//******************С�����ƶ�	**************//			
			case 0:		yidong();
				break;

//******************��е�ۿ���**************//                                                                                         q
     	case 1:	
							if(chary[3]>1 || chary[3]<-1 || chary[3]==0)
							{
								SG90_yaw=(3*chary[3]+90);//��						
							}
							if(chary[4]>1 || chary[4]<-1 || chary[4]==0)
							{
								SG90_yroll_1=(1.5*chary[4]+90);//����
								SG90_yroll_2=(1.5*chary[4]+90);//����
							}

							if(chary[5]>7) //ץȡ
							{
									TIM_SetCompare1(TIM1, angle_to_pulse(170));
							}
							if(chary[5]<-7) //ץȡ
							{
									TIM_SetCompare1(TIM1, angle_to_pulse(60));
							}										
							Set_Servos_Angles(SG90_yroll_2,SG90_yaw,SG90_yroll_1); // PA8, PA9������, PA10, PA11������
				break; 

//*****************��ʪ�ȵķ���*************//					
			case 2:		huanjing();
				break;		
		}
	}	
}

