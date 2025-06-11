#include "stm32f10x.h"

// PWM参数配置
#define PWM_PERIOD      20000   // 20ms周期（舵机标准）
#define PRESCALER_VALUE 72      // 72MHz/72=1MHz → 1计数=1us

/********************* 硬件配置说明 *********************
 * 引脚映射：
 * - PA8  → TIM1_CH1 (默认功能)
 * - PA9  → TIM1_CH2 (默认功能)
 * - PA10 → TIM1_CH3 (默认功能)
 * - PA11 → TIM1_CH4 (需部分重映射)
 * 注意：所有舵机共地，建议外接5V电源供电
 ******************************************************/

void TIM1_PWM_Init(void) 
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef TIM_OCStruct;

    // 1. 开启必要的外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE);

    // 2. 配置GPIO为复用推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    // 复用推挽模式
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  // 高速输出
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. 启用TIM1部分重映射（关键！将CH4映射到PA11）
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);

    // 4. 配置TIM1时基单元
    TIM_TimeBaseStruct.TIM_Period = PWM_PERIOD - 1;      // 自动重载值
    TIM_TimeBaseStruct.TIM_Prescaler = PRESCALER_VALUE - 1; // 分频系数
    TIM_TimeBaseStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    // 5. 配置所有PWM通道
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;       // PWM模式1
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;     // 高电平有效

    // 通道1（PA8）
    TIM_OCStruct.TIM_Pulse = 1500;  // 初始1.5ms
    TIM_OC1Init(TIM1, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // 通道2（PA9）
    TIM_OCStruct.TIM_Pulse = 1500;
    TIM_OC2Init(TIM1, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // 通道3（PA10）
    TIM_OCStruct.TIM_Pulse = 1500;
    TIM_OC3Init(TIM1, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // 通道4（PA11）需特别注意重映射
    TIM_OCStruct.TIM_Pulse = 1500;
    TIM_OC4Init(TIM1, &TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // 6. 高级定时器关键配置
    TIM_ARRPreloadConfig(TIM1, ENABLE);       // 使能ARR预装载
    TIM_CtrlPWMOutputs(TIM1, ENABLE);         // 必须启用主输出
    TIM_Cmd(TIM1, ENABLE);                    // 启动定时器
}


/* 角度转脉宽计算（内部函数） */
 uint16_t angle_to_pulse(uint8_t angle) 
	{
    // 角度限制在0-180之间
    if(angle > 180) angle = 180;
    
    // 计算脉宽：500us（0°）~2500us（180°）
    return 500 + (angle * 2000) / 180; // 整数运算避免浮点
 }

 #include "Delay.h"
 
/* 设置四个舵机角度（直接填入0-180度） */
void Set_Servos_Angles(uint8_t angle2, uint8_t angle3, uint8_t angle4)
	{
    TIM_SetCompare2(TIM1, angle_to_pulse(angle2)); // 通道2（PA9）
    TIM_SetCompare3(TIM1, angle_to_pulse(angle3)); // 通道3（PA10）
    TIM_SetCompare4(TIM1, angle_to_pulse(angle4)); // 通道4（PA11）
	}
