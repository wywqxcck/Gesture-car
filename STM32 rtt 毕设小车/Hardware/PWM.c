#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
	
		//初始化GPIO口 PB
	  GPIO_InitTypeDef GPIO_InitStructure;	
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO A6 A7
		
	
		//使用内部时钟
		TIM_InternalClockConfig(TIM4);
		TIM_InternalClockConfig(TIM1);
		//配置时基单元参数
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//定时器不分频
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
		TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR自动重装值
		TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;//PSC预分频值
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//到达ARR触发一次中断 停止计数
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);//初始化单元
		
		
		//输出比较结构体配置
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCStructInit(&TIM_OCInitStructure);//补全结构体中未配置参数
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择PWM模式1
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性选择
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);//初始化 TIM4 OC1
		TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);//使能CCR1自动重装
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);//初始化 TIM4 OC2	
		TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);//使能CCR2自动重装

	
		TIM_ARRPreloadConfig(TIM4,ENABLE);//开启预装载
		TIM_Cmd(TIM4, ENABLE);//开启定时器4
		
		TIM4->CCR1 = 0;
		TIM4->CCR2 = 0;	

		TIM1->CCR4 = 0;
}

//设置PMW1比较直  为Compare 即输出比较值

 void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM4, Compare);
}

void PWM_SetCompare2(uint16_t Compare)
{                                                                        
	TIM_SetCompare2(TIM4, Compare);
}



