/*
 * Buzzer.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_BUZZER_H_
#define CODE_BUZZER_H_

#include "zf_gpio.h"
#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "zf_stm_systick.h"

#define BEEP_PIN   P33_10       //定义蜂鸣器引脚
void Buzzer_init(void);
void Start_Buzzer(void);
void Close_Buzzer(void);
void Beep_10ms(uint8 bt);

extern uint8 start_beep_flag;
extern uint8 beep_time;
extern uint8 Buzzer_time;
#endif /* CODE_BUZZER_H_ */
