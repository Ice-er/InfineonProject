/*
 * Motor.c
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */

#include"Motor.h"
#include "SEEKFREE_FUN.h"
#include "zf_gpt12.h"
#include "zf_gtm_pwm.h"
short Motor_Bias1, Motor_Last_Bias1, Motor_Integration1; // 电机所用参数
float Motor_Kp1 = 35,Motor_Ki1 = 25;
short Motor_Bias2, Motor_Last_Bias2, Motor_Integration2; // 电机所用参数
float Motor_Kp2 = 35,Motor_Ki2 = 25;
int PWM_Motor1,PWM_Motor2;
int Speed_Left,Speed_Right;
int Velocity1 = 30;
int Velocity2 = 30;
short Flag_Stop = 1;

void Motor_init()
{
    //卓晴大大的推文中，建议电磁组电机频率选用13K-17K
    gtm_pwm_init(MOTOR2_A, 13000, 0);
    gtm_pwm_init(MOTOR2_B, 13000, 0);
    gtm_pwm_init(MOTOR1_A, 13000, 0);
    gtm_pwm_init(MOTOR1_B, 13000, 0);
    Set_MotorLeft_Speed(0);
    Set_MotorRight_Speed(0);
}
void Set_MotorLeft_Speed(int pwm)
{
    if(0<=pwm) //左电机   正转
    {
        pwm_duty(MOTOR1_A, 0);
        pwm_duty(MOTOR1_B, pwm);
    }
    else                //左电机   反转
    {
        pwm_duty(MOTOR1_A, -pwm);
        pwm_duty(MOTOR1_B, 0);
    }
}

void Set_MotorRight_Speed(int pwm)   //右电机控制
{
    if(0<=pwm) //右电机   正转
    {
        pwm_duty(MOTOR2_A, 0);
        pwm_duty(MOTOR2_B, pwm);
    }
    else                //右电机   反转
    {
        pwm_duty(MOTOR2_A, -pwm);
        pwm_duty(MOTOR2_B, 0);
    }
}



void Set_Speed()
{
    static int error_s,Pwm_Left,last_error_s;
    static int Pwm_Right,error_s2,last_error_s2;

    Speed_Left = myabs(Get_LeftSpeed());
    Speed_Right = myabs(Get_RightSpeed());

    error_s=Velocity1-Speed_Left;               //计算偏差
    Pwm_Left+=Motor_Kp1*(error_s-last_error_s)+Motor_Ki1*error_s;//增量PI
    last_error_s=error_s;                     //保存上一次偏差

    error_s2=Velocity2-Speed_Right;               //计算偏差
    Pwm_Right+=Motor_Kp2*(error_s2-last_error_s2)+Motor_Ki2*error_s2;//增量PI
    last_error_s2=error_s2;                     //保存上一次偏差
    if(Flag_Stop==1)
    {
        Pwm_Left = 0;
        Pwm_Right = 0;
    }
    if(Pwm_Left<-8000) Pwm_Left=-8000;
    else if(Pwm_Left>8000) Pwm_Left=8000;//限幅
    Set_MotorLeft_Speed(Pwm_Left);
    if(Pwm_Right<-8000) Pwm_Right=-8000;
    else if(Pwm_Right>8000) Pwm_Right=8000;//限幅
    Set_MotorRight_Speed(Pwm_Right);
    //Set_Motor_Speed(Speed);
}
