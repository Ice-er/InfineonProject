/*
 * Servo_Motor.h
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */

#ifndef CODE_SERVO_MOTOR_H_
#define CODE_SERVO_MOTOR_H_
#include "IfxGtm_Atom_Pwm.h"
#include "zf_gtm_pwm.h"
#define S_MOTOR_PIN   ATOM1_CH1_P33_9       //����������
#define Servo_duty_Center 655  //�����ֵ
#define Servo_max 765  //��������ֵ
#define Servo_min 545  //����Ҵ���ֵ
extern uint16 Servo_duty;

void ServoMotor_init(void);
void Servo_Control(uint16 duty);

#endif /* CODE_SERVO_MOTOR_H_ */
