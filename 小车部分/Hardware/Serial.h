#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

void Serial1_Init(void);
void Serial1_SendByte(uint8_t Byte);
void Serial1_SendArray(uint8_t *Array, uint16_t Length);
void Serial1_SendString(char *String);
void Serial1_SendNumber(uint32_t Number, uint8_t Length);
void Serial1_Printf(char *format, ...);

uint8_t Serial1_GetRxFlag(void);
uint8_t Serial1_GetRxData(void);

#endif
