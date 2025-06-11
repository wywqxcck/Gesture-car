#ifndef __SG90_H
#define __SG90_H

void TIM1_PWM_Init(void);
 uint16_t angle_to_pulse(uint8_t angle);
void Set_Servos_Angles( uint8_t angle2, uint8_t angle3, uint8_t angle4);
void DUOJI(void);

#endif
