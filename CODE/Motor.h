/*
 * Motor.h
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_
#include"Encoder.h"

#define MOTOR2_A   ATOM0_CH4_P02_4   //定义右电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH5_P02_5   //定义右电机反转PWM引脚

#define MOTOR1_A   ATOM0_CH6_P02_6   //定义左电机正转PWM引脚
#define MOTOR1_B   ATOM0_CH7_P02_7   //定义左电机反转PWM引脚

void Motor_init(void);
void Set_MotorLeft_Speed(int pwm);
void Set_MotorRight_Speed(int pwm);
void Set_Speed(void);

extern float Motor_Kp1,Motor_Ki1;
extern float Motor_Kp2,Motor_Ki2;
extern int Velocity1,Velocity2;
extern int Speed_Left,Speed_Right;
extern short Flag_Stop;
extern int PWM_Motor1,PWM_Motor2;
#endif /* CODE_MOTOR_H_ */
