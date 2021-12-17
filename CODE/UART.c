/*
 * UART.c
 *
 *  Created on: 2021��11��14��
 *      Author: Peng
 */


#include "UART.h"
#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "SEEKFREE_WIRELESS.h"
#include "Motor.h"
#include <stdio.h>
uint8 Data[10];
void vcan_sendware(uint8 *wareaddr,uint8 *wareaddr1,uint8 *wareaddr2,uint32 waresize,uint32 waresize1,uint32 waresize2)
{
    uint8 cmdf[2] = {0x03, 0xfc};    //���ڵ��� ʹ�õ�ǰ����
    uint8 cmdr[2] = {0xfc, 0x03};    //���ڵ��� ʹ�õĺ�����

    seekfree_wireless_send_buff(cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    seekfree_wireless_send_buff(wareaddr,waresize);    //��������
    seekfree_wireless_send_buff(wareaddr1,waresize1);
    seekfree_wireless_send_buff(wareaddr2,waresize2);
    seekfree_wireless_send_buff(cmdr, sizeof(cmdr));    //���ͺ�����
}

void Speed_Send()//�۲��ٶ�
{
    char str1[10];
    char str2[10];
    sprintf(str1,"%3d   ",Speed_Left);
    sprintf(str2,"%3d\n",Speed_Right);
    uart_putstr(UART_0, str1);
    uart_putstr(UART_0, str2);
}



void UART_Task()
{
 /*   uart_getchar(UART_0,&Data);
    if(Data=='1')
    {
        Task1();
        seekfree_wireless_send_buff(Data,sizeof(Data));
    }*/
}

void Task1()
{
    Velocity1 +=2;
    Velocity2 +=2;
}
