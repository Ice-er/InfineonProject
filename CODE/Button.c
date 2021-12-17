/*
 * Button.c
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */
//���尴������
#include "Button.h"
#include "zf_spi.h"
#include "zf_gpio.h"
#include "zf_assert.h"
#include "zf_stm_systick.h"
#include "SEEKFREE_PRINTF.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "Motor.h"
//#include "Direction.h"
//���뿪��״̬����
uint8 sw1_status;
uint8 sw2_status;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

void Button_init()
{
    //������ʼ��
    gpio_init(KEY1,GPI,0,PULLUP);
    gpio_init(KEY2,GPI,0,PULLUP);
    gpio_init(KEY3,GPI,0,PULLUP);
    gpio_init(KEY4,GPI,0,PULLUP);

    //���뿪�س�ʼ��
    gpio_init(SW1,GPI,0,PULLUP);
    gpio_init(SW2,GPI,0,PULLUP);
}

void Button_Process()
{
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    key1_status = gpio_get(KEY1);
    key2_status = gpio_get(KEY2);
    key3_status = gpio_get(KEY3);
    key4_status = gpio_get(KEY4);
    //��⵽��������֮��  ���ſ���λ��־λ
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;

    if(key1_flag==1)
    {
            key1_flag = 0;
            Flag_Stop = 0;
            //D_Kp += 0.2;
     }
    if(key2_flag==1)
    {
            key2_flag = 0;
            Flag_Stop = 1;
            //D_Kp -= 0.2;
     }
    if(key3_flag==1)
    {
            key3_flag = 0;
            //Motor_Kp1 += 1;
           // Motor_Kp2 += 1;
            //D_Kd += 0.05;
     }
    if(key4_flag==1)
    {
            key4_flag = 0;
           // Motor_Kp1 -= 1;
            //Motor_Kp2 -= 1;
            //D_Kd -= 0.05;
     }

}

