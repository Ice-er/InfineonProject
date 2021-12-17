/*
 * LED.h
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */

#ifndef CODE_LED_H_
#define CODE_LED_H_

#include "common.h"
#include "zf_gpio.h"
#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "zf_stm_systick.h"

#define LED1   P21_4       //����LED����
#define LED2   P21_5       //����LED����
#define LED3   P20_8       //����LED����
#define LED4   P20_9       //����LED����

void LED_Init(void);
void LED_Control(int x);
void LED_Set(int x);
void LED_Reset(int x);
#endif /* CODE_LED_H_ */
