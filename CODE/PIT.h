/*
 * PIT.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_PIT_H_
#define CODE_PIT_H_

#include "IfxCcu6_Timer.h"
#include "SysSe/Bsp/Bsp.h"
#include "isr_config.h"
#include "zf_ccu6_pit.h"

void PIT_Speed(uint16 t);//速度闭环控制定时中断
void PIT_Servo(uint16 t);//方向控制定时中断
void PIT_Servo2(uint16 t);//方向控制定时中断

#endif /* CODE_PIT_H_ */
