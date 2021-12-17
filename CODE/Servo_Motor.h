/*
 * Servo_Motor.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_SERVO_MOTOR_H_
#define CODE_SERVO_MOTOR_H_
#include "IfxGtm_Atom_Pwm.h"
#include "zf_gtm_pwm.h"
#define S_MOTOR_PIN   ATOM1_CH1_P33_9       //定义舵机引脚
#define Servo_duty_Center 655  //舵机中值
#define Servo_max 765  //舵机左打死值
#define Servo_min 545  //舵机右打死值
extern uint16 Servo_duty;

void ServoMotor_init(void);
void Servo_Control(uint16 duty);

#endif /* CODE_SERVO_MOTOR_H_ */
