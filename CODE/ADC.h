/*
 * ADC.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_ADC_H_
#define CODE_ADC_H_

//#include "Evadc/Adc/IfxEvadc_Adc.h"

#include "zf_assert.h"
#include "zf_vadc.h"
#include "stdio.h"

void Adc_init(void);
void Get_Adc(uint8 mean_times);
void Normalization(void);
void quick_sort(uint16 s[], uint8 l, uint8 r);//快速排序
void Kalman_Filter(void);//卡尔曼滤波

extern uint16 ad_value[16],ad_bat,ad_stop;
extern uint8 AD[16];
extern uint16 Max[16],Min[16],Range[16];

#endif /* CODE_ADC_H_ */
