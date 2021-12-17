/*
 * Button.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_BUTTON_H_
#define CODE_BUTTON_H_
#include "common.h"
#include "zf_gpio.h"
#include "Servo_Motor.h"
//定义按键引脚
#define KEY1    P22_0
#define KEY2    P22_1
#define KEY3    P22_2
#define KEY4    P22_3
//定义拨码开关引脚
#define SW1     P33_12
#define SW2     P33_13
void Button_Process(void);
void Button_init(void);

#endif /* CODE_BUTTON_H_ */
