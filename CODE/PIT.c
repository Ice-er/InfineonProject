/*
 * PIT.c
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */
#include "Pit.h"
void PIT_Speed(uint16 t)//�ٶȱջ����ƶ�ʱ�ж�
{
    //ʹ��CCU6_0ģ���ͨ��0 ����һ�� t ms�������ж�
    pit_interrupt_ms(CCU6_0, PIT_CH0,t);
}
void PIT_Servo(uint16 t)//������ƶ�ʱ�ж�
{
    //ʹ��CCU6_0ģ���ͨ��1 ����һ�� t ms�������ж�
    pit_interrupt_ms(CCU6_0, PIT_CH1,t);
}
void PIT_Servo2(uint16 t)//������ƶ�ʱ�ж�
{
    //ʹ��CCU6_1ģ���ͨ��0 ����һ�� t ms�������ж�
    pit_interrupt_ms(CCU6_1, PIT_CH0,t);
}

