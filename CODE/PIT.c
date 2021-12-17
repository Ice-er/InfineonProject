/*
 * PIT.c
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */
#include "Pit.h"
void PIT_Speed(uint16 t)//速度闭环控制定时中断
{
    //使用CCU6_0模块的通道0 产生一个 t ms的周期中断
    pit_interrupt_ms(CCU6_0, PIT_CH0,t);
}
void PIT_Servo(uint16 t)//方向控制定时中断
{
    //使用CCU6_0模块的通道1 产生一个 t ms的周期中断
    pit_interrupt_ms(CCU6_0, PIT_CH1,t);
}
void PIT_Servo2(uint16 t)//方向控制定时中断
{
    //使用CCU6_1模块的通道0 产生一个 t ms的周期中断
    pit_interrupt_ms(CCU6_1, PIT_CH0,t);
}

