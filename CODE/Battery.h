/*
 * Battery.h
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: Peng
 */

#ifndef CODE_BATTERY_H_
#define CODE_BATTERY_H_
#include "common.h"
//#include "Evadc/Adc/IfxEvadc_Adc.h"
#include "zf_assert.h"
#include "zf_vadc.h"
#include "stdio.h"
#include "Buzzer.h"

extern uint16  voltage;

void Bat_Volt_init(void);
uint16 Get_Bat_Volt(void);


#endif /* CODE_BATTERY_H_ */
