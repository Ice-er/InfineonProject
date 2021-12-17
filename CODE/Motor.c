/*
 * Motor.c
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */

#include"Motor.h"
#include "SEEKFREE_FUN.h"
#include "zf_gpt12.h"
#include "zf_gtm_pwm.h"
short Motor_Bias1, Motor_Last_Bias1, Motor_Integration1; // ������ò���
float Motor_Kp1 = 35,Motor_Ki1 = 25;
short Motor_Bias2, Motor_Last_Bias2, Motor_Integration2; // ������ò���
float Motor_Kp2 = 35,Motor_Ki2 = 25;
int PWM_Motor1,PWM_Motor2;
int Speed_Left,Speed_Right;
int Velocity1 = 30;
int Velocity2 = 30;
short Flag_Stop = 1;

void Motor_init()
{
    //׿����������У�����������Ƶ��ѡ��13K-17K
    gtm_pwm_init(MOTOR2_A, 13000, 0);
    gtm_pwm_init(MOTOR2_B, 13000, 0);
    gtm_pwm_init(MOTOR1_A, 13000, 0);
    gtm_pwm_init(MOTOR1_B, 13000, 0);
    Set_MotorLeft_Speed(0);
    Set_MotorRight_Speed(0);
}
void Set_MotorLeft_Speed(int pwm)
{
    if(0<=pwm) //����   ��ת
    {
        pwm_duty(MOTOR1_A, 0);
        pwm_duty(MOTOR1_B, pwm);
    }
    else                //����   ��ת
    {
        pwm_duty(MOTOR1_A, -pwm);
        pwm_duty(MOTOR1_B, 0);
    }
}

void Set_MotorRight_Speed(int pwm)   //�ҵ������
{
    if(0<=pwm) //�ҵ��   ��ת
    {
        pwm_duty(MOTOR2_A, 0);
        pwm_duty(MOTOR2_B, pwm);
    }
    else                //�ҵ��   ��ת
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

    error_s=Velocity1-Speed_Left;               //����ƫ��
    Pwm_Left+=Motor_Kp1*(error_s-last_error_s)+Motor_Ki1*error_s;//����PI
    last_error_s=error_s;                     //������һ��ƫ��

    error_s2=Velocity2-Speed_Right;               //����ƫ��
    Pwm_Right+=Motor_Kp2*(error_s2-last_error_s2)+Motor_Ki2*error_s2;//����PI
    last_error_s2=error_s2;                     //������һ��ƫ��
    if(Flag_Stop==1)
    {
        Pwm_Left = 0;
        Pwm_Right = 0;
    }
    if(Pwm_Left<-8000) Pwm_Left=-8000;
    else if(Pwm_Left>8000) Pwm_Left=8000;//�޷�
    Set_MotorLeft_Speed(Pwm_Left);
    if(Pwm_Right<-8000) Pwm_Right=-8000;
    else if(Pwm_Right>8000) Pwm_Right=8000;//�޷�
    Set_MotorRight_Speed(Pwm_Right);
    //Set_Motor_Speed(Speed);
}
