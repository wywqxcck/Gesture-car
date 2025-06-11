#ifndef __nRF24L01_API_H
#define __nRF24L01_API_H

#include "stm32f10x.h"                  // Device header

int8_t SPI_SwapByte(int8_t byte);
int8_t NRF24L01_Write_Reg(int8_t reg,int8_t value);
int8_t NRF24L01_Read_Reg(int8_t reg);
int8_t NRF24L01_Read_Buf(int8_t reg,int8_t *pBuf, int8_t len);
int8_t NRF24L01_Write_Buf(int8_t reg, int8_t *pBuf, int8_t len);
int8_t NRF24L01_GetRxBuf(int8_t *rxbuf);
int8_t NRF24L01_SendTxBuf(int8_t *txbuf);
int8_t NRF24L01_Check(void);
void NRF24L01_RT_Init(void);
void NRF24L01_Init(void);
void NRF24L01_SendBuf(int8_t *Buf);
void NRF24L01_Pin_Init(void);
int8_t NRF24L01_Get_Value_Flag(void);

#endif
