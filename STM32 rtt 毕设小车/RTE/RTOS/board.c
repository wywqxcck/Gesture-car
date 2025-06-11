#include <rthw.h>
#include <rtthread.h>
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "board.h"
#include "OLED.h"
#if 0
/*========================================================*/ 
/* �ں�����NVIC��صļĴ������� */
#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

/* �ⲿʱ�Ӻͺ������� */
extern void SystemCoreClockUpdate(void);
extern uint32_t SystemCoreClock;

/* ϵͳ��ʱ��SysTick��ʼ�� */
static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }

    _SYSTICK_LOAD = ticks - 1;
    _SYSTICK_PRI = 0xFF;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;

    return 0;
}
#endif
/*=================����RT_Thread�Ķѵ��ڲ�RAM=======================*/

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE 1024
static rt_uint32_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_os_tick_callback(void)
{
    rt_interrupt_enter();
    
    rt_tick_increase();

    rt_interrupt_leave();
}

void SysTick_Handler()
{
	 rt_interrupt_enter();
	  rt_tick_increase();
	  rt_interrupt_leave();
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{


    /* SysTick��ʼ�� */
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

//#error "TODO 1: OS Tick Configuration."
    /* 
     * TODO 1: OS Tick Configuration
     * Enable the hardware timer and call the rt_os_tick_callback function
     * periodically with the frequency RT_TICK_PER_SECOND. 
     */
	LED_Init();
	USART_Config();
	Key_Init();
	OLED_Init ();

    /* Call components board initial (use INIT_BOARD_EXPORT()) */

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)       //��̬ջ�ڴ�
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get()); // ��̬ջ�ڴ�
#endif
}

#ifdef RT_USING_CONSOLE
static int uart_init(void)
{
//#error "TODO 2: Enable the hardware uart and config baudrate."
	USART_Config();
    return 0;
}
INIT_BOARD_EXPORT(uart_init);


#endif

