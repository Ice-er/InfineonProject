/*
 * LED.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_LED_H_
#define CODE_LED_H_

#include "common.h"
#include "zf_gpio.h"
#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "zf_stm_systick.h"

#define LED1   P21_4       //定义LED引脚
#define LED2   P21_5       //定义LED引脚
#define LED3   P20_8       //定义LED引脚
#define LED4   P20_9       //定义LED引脚

void LED_Init(void);
void LED_Control(int x);
void LED_Set(int x);
void LED_Reset(int x);
#endif /* CODE_LED_H_ */
