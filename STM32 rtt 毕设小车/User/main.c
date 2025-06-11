#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024
/* ���ڲ�SRAM�������һ���־�̬�ڴ�����Ϊrtt�Ķѿռ䣬��������Ϊ4KB */
static uint32_t rt_heap[RT_HEAP_SIZE];
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/* �ò��ִ����ȡ�Ժ���rt_hw_board_init() */
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
//rt_system_heap_init((void*)HEAP_BEGIN, (void*)SRAM_END);
rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

#include "board.h"
#include <rtthread.h>
#include "stm32f10x.h"                  // Device header
#include "car.h"
#include "Delay.h"
#include "OLED.h"
#include "NRF24L01.h"
#include "DHT11.h"
#include "Serial.h"
#include "SG90.h"
#include "PWM.h"

static  rt_thread_t led1_thread =RT_NULL ;

extern int8_t wenshidu[4] ;
extern int8_t chary[9] ;
int8_t xuanze=0;
int8_t SG90_yaw=0,SG90_yroll_1=0,SG90_yroll_2=0;//�����������
// ץ�� ����2 �� ���ң� ��1��

static void led1_thread_entry(void* parameter); //��������




/* �����߳̿�ջʱҪ��RT_ALIGN_SIZE���ֽڶ��� */
ALIGN(RT_ALIGN_SIZE)
/* �����߳�ջ */


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
	
		led1_thread = 
		rt_thread_create("led1",                //�߳�����
								led1_thread_entry,     //�̵߳���ں���
								RT_NULL,               //�߳���ں�������
								512,									 //�߳�ջ��С
								3,                     //�̵߳����ȼ�
								20);                    //�̵߳�ʱ��Ƭ

//�����̣߳���������			
if(led1_thread != RT_NULL)
		rt_thread_startup(led1_thread);
else
	return -1;



}
void led1_thread_entry( void *parameter)
{
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


