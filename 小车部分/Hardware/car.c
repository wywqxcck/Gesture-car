#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "NRF24L01.h"
#include "OLED.h"

void MotorAll_Init(void)
{
	//开启电机驱动口的四个GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//设置右路电机速度 PWM
void MotorR_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)//Speed值为正
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);//电机正转
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare1(Speed);//设置Speed转速
	}
	else//Speed值为负
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);//电机反转
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare1(-Speed);//设为-Speed转速
	}
}

//设置左路电机PWM 速度
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

// 小车随着传递的信息运动//
 int8_t x=0 , y=0;//转向和直向防冲突
int8_t chary[9] = {0};

	
void yidong()
{		
//*************************前后**************************//
		if(x==0)			
		{				
			if(chary[1]> 10) 
			{	
				MotorR_SetSpeed(-chary[1]*2);  
				MotorL_SetSpeed(chary[1]*2);	 //应该是轮子因素插反了
			OLED_Clear();	OLED_ShowChinese(40,0,"前进"); OLED_Update();
			}
			if(chary[1]<-10) 
			{		
				MotorR_SetSpeed(-chary[1]*2);
				MotorL_SetSpeed(chary[1]*2);
			OLED_Clear();	OLED_ShowChinese(40,32,"后退"); OLED_Update();
			}				
			if((-10<chary[1] && chary[1]<=0) || (0<=chary[1] && chary[1]<10) ) //放进去不然会停止转动
			{
				x=1;
			}		
			if(x==1)
			{
				chary[1]=0;
				MotorR_SetSpeed(-chary[1]*2+chary[2]*2);  
				MotorL_SetSpeed(chary[1]*2+chary[2]*2);	 //应该是轮子因素插反了
				x=0;
			}		
		}
//*********************左右*************************//		
		if(y==0)
		{			
			if(chary[2]>10 )  //左转
			{		
				MotorR_SetSpeed(-chary[2]*2);  
				MotorL_SetSpeed(-chary[2]*2);	 //]应该是轮子因素插反了
			OLED_Clear();	OLED_ShowChinese(0,16,"左转"); OLED_Update();
			}			
			if(chary[2]<-10 ) //右转
			{
				MotorR_SetSpeed(-chary[2]*2);;
				MotorL_SetSpeed(-chary[2]*2);		
			OLED_Clear();OLED_ShowChinese(73,16,"右转"); OLED_Update();
			}		

			if((-10<chary[2] && chary[2]<=0) || (0<=chary[2] && chary[2]<10) )
			{
				y=1;
			}		
			if(y==1)
			{
				chary[2]=0;
				MotorR_SetSpeed(-chary[1]*2-chary[2]*2);  
				MotorL_SetSpeed(chary[1]*2-chary[2]*2);	 //应该是轮子因素插反了
				y=0;
			}		
		}
}

void run_stop()
{
	MotorR_SetSpeed(0);
	MotorL_SetSpeed(0);
}
