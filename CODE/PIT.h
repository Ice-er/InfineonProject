/*
 * PIT.h
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */

#ifndef CODE_PIT_H_
#define CODE_PIT_H_

#include "IfxCcu6_Timer.h"
#include "SysSe/Bsp/Bsp.h"
#include "isr_config.h"
#include "zf_ccu6_pit.h"

void PIT_Speed(uint16 t);//�ٶȱջ����ƶ�ʱ�ж�
void PIT_Servo(uint16 t);//������ƶ�ʱ�ж�
void PIT_Servo2(uint16 t);//������ƶ�ʱ�ж�

#endif /* CODE_PIT_H_ */
