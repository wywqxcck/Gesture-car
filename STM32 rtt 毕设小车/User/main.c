#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024
/* 从内部SRAM里面分配一部分静态内存来作为rtt的堆空间，这里配置为4KB */
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

/* 该部分代码截取自函数rt_hw_board_init() */
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
int8_t SG90_yaw=0,SG90_yroll_1=0,SG90_yroll_2=0;//舵机的三个轴
// 抓下 ，竖2 ， 左右， 竖1；

static void led1_thread_entry(void* parameter); //函数声明




/* 定义线程控栈时要求RT_ALIGN_SIZE个字节对齐 */
ALIGN(RT_ALIGN_SIZE)
/* 定义线程栈 */


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
		rt_thread_create("led1",                //线程名字
								led1_thread_entry,     //线程的入口函数
								RT_NULL,               //线程入口函数参数
								512,									 //线程栈大小
								3,                     //线程的优先级
								20);                    //线程的时间片

//启动线程，开启调度			
if(led1_thread != RT_NULL)
		rt_thread_startup(led1_thread);
else
	return -1;



}
void led1_thread_entry( void *parameter)
{
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


