#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "NRF24L01.h"
#include "OLED.h"

void MotorAll_Init(void)
{
	//������������ڵ��ĸ�GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//������·����ٶ� PWM
void MotorR_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)//SpeedֵΪ��
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);//�����ת
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare1(Speed);//����Speedת��
	}
	else//SpeedֵΪ��
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);//�����ת
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare1(-Speed);//��Ϊ-Speedת��
	}
}

//������·���PWM �ٶ�
void MotorL_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare2(-Speed);
	}
}

// С�����Ŵ��ݵ���Ϣ�˶�//
 int8_t x=0 , y=0;//ת���ֱ�����ͻ
int8_t chary[9] = {0};

	
void yidong()
{		
//*************************ǰ��**************************//
		if(x==0)			
		{				
			if(chary[1]> 10) 
			{	
				MotorR_SetSpeed(-chary[1]*2);  
				MotorL_SetSpeed(chary[1]*2);	 //Ӧ�����������ز巴��
			OLED_Clear();	OLED_ShowChinese(40,0,"ǰ��"); OLED_Update();
			}
			if(chary[1]<-10) 
			{		
				MotorR_SetSpeed(-chary[1]*2);
				MotorL_SetSpeed(chary[1]*2);
			OLED_Clear();	OLED_ShowChinese(40,32,"����"); OLED_Update();
			}				
			if((-10<chary[1] && chary[1]<=0) || (0<=chary[1] && chary[1]<10) ) //�Ž�ȥ��Ȼ��ֹͣת��
			{
				x=1;
			}		
			if(x==1)
			{
				chary[1]=0;
				MotorR_SetSpeed(-chary[1]*2+chary[2]*2);  
				MotorL_SetSpeed(chary[1]*2+chary[2]*2);	 //Ӧ�����������ز巴��
				x=0;
			}		
		}
//*********************����*************************//		
		if(y==0)
		{			
			if(chary[2]>10 )  //��ת
			{		
				MotorR_SetSpeed(-chary[2]*2);  
				MotorL_SetSpeed(-chary[2]*2);	 //]Ӧ�����������ز巴��
			OLED_Clear();	OLED_ShowChinese(0,16,"��ת"); OLED_Update();
			}			
			if(chary[2]<-10 ) //��ת
			{
				MotorR_SetSpeed(-chary[2]*2);;
				MotorL_SetSpeed(-chary[2]*2);		
			OLED_Clear();OLED_ShowChinese(73,16,"��ת"); OLED_Update();
			}		

			if((-10<chary[2] && chary[2]<=0) || (0<=chary[2] && chary[2]<10) )
			{
				y=1;
			}		
			if(y==1)
			{
				chary[2]=0;
				MotorR_SetSpeed(-chary[1]*2-chary[2]*2);  
				MotorL_SetSpeed(chary[1]*2-chary[2]*2);	 //Ӧ�����������ز巴��
				y=0;
			}		
		}
}

void run_stop()
{
	MotorR_SetSpeed(0);
	MotorL_SetSpeed(0);
}
