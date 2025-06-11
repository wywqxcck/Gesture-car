#include "stm32f10x.h"

// PWM��������
#define PWM_PERIOD      20000   // 20ms���ڣ������׼��
#define PRESCALER_VALUE 72      // 72MHz/72=1MHz �� 1����=1us

/********************* Ӳ������˵�� *********************
 * ����ӳ�䣺
 * - PA8  �� TIM1_CH1 (Ĭ�Ϲ���)
 * - PA9  �� TIM1_CH2 (Ĭ�Ϲ���)
 * - PA10 �� TIM1_CH3 (Ĭ�Ϲ���)
 * - PA11 �� TIM1_CH4 (�貿����ӳ��)
 * ע�⣺���ж�����أ��������5V��Դ����
 ******************************************************/

void TIM1_PWM_Init(void) 
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef TIM_OCStruct;

    // 1. ������Ҫ������ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE);

    // 2. ����GPIOΪ�����������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    // ��������ģʽ
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  // �������
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. ����TIM1������ӳ�䣨�ؼ�����CH4ӳ�䵽PA11��
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);

    // 4. ����TIM1ʱ����Ԫ
    TIM_TimeBaseStruct.TIM_Period = PWM_PERIOD - 1;      // �Զ�����ֵ
    TIM_TimeBaseStruct.TIM_Prescaler = PRESCALER_VALUE - 1; // ��Ƶϵ��
    TIM_TimeBaseStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    // 5. ��������PWMͨ��
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;       // PWMģʽ1
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable; // ���ʹ��
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;     // �ߵ�ƽ��Ч

    // ͨ��1��PA8��
    TIM_OCStruct.TIM_Pulse = 1500;  // ��ʼ1.5ms
    TIM_OC1Init(TIM1, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // ͨ��2��PA9��
    TIM_OCStruct.TIM_Pulse = 1500;
    TIM_OC2Init(TIM1, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // ͨ��3��PA10��
    TIM_OCStruct.TIM_Pulse = 1500;
    TIM_OC3Init(TIM1, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // ͨ��4��PA11�����ر�ע����ӳ��
    TIM_OCStruct.TIM_Pulse = 1500;
    TIM_OC4Init(TIM1, &TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // 6. �߼���ʱ���ؼ�����
    TIM_ARRPreloadConfig(TIM1, ENABLE);       // ʹ��ARRԤװ��
    TIM_CtrlPWMOutputs(TIM1, ENABLE);         // �������������
    TIM_Cmd(TIM1, ENABLE);                    // ������ʱ��
}


/* �Ƕ�ת������㣨�ڲ������� */
 uint16_t angle_to_pulse(uint8_t angle) 
	{
    // �Ƕ�������0-180֮��
    if(angle > 180) angle = 180;
    
    // ��������500us��0�㣩~2500us��180�㣩
    return 500 + (angle * 2000) / 180; // ����������⸡��
 }

 #include "Delay.h"
 
/* �����ĸ�����Ƕȣ�ֱ������0-180�ȣ� */
void Set_Servos_Angles(uint8_t angle2, uint8_t angle3, uint8_t angle4)
	{
    TIM_SetCompare2(TIM1, angle_to_pulse(angle2)); // ͨ��2��PA9��
    TIM_SetCompare3(TIM1, angle_to_pulse(angle3)); // ͨ��3��PA10��
    TIM_SetCompare4(TIM1, angle_to_pulse(angle4)); // ͨ��4��PA11��
	}
