#include "usart.h"
#include <rtthread.h>
 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */

void USART_Config( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
 
    // 打开串口GPIO的时钟
    DEBUG_USART_GPIO_APBxClkCmd( DEBUG_USART_GPIO_CLK, ENABLE );
 
    // 打开串口外设的时钟
    DEBUG_USART_APBxClkCmd( DEBUG_USART_CLK, ENABLE );
 
    // 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure );
 
    // 将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init( DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure );
 
    // 配置串口的工作参数
    // 配置波特率
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    // 配置 针数据字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 配置校验位
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    // 配置硬件流控制
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;
    // 配置工作模式，收发一起
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 完成串口的初始化配置
    USART_Init( DEBUG_USARTx, &USART_InitStructure );
 
    // 使能串口
    USART_Cmd( DEBUG_USARTx, ENABLE );
}
