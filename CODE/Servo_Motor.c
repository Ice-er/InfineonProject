/*
 * Servo_Motor.c
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */
#include"Servo_Motor.h"
uint16 Servo_duty = 655;
void ServoMotor_init(void)
{
//    uint16 duty0;
//    duty0 = 1.56 * 10000 / 20;//���˵��е��λ����
    gtm_pwm_init(S_MOTOR_PIN, 50, Servo_duty_Center);
}
void Servo_Control(uint16 duty)
{
    pwm_duty(S_MOTOR_PIN,duty);
}


