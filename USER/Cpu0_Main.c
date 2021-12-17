/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#pragma section all "cpu0_dsram"
#include "Button.h"
#include"Buzzer.h"
#include"LED.h"
#include"Servo_Motor.h"
#include"Motor.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_MT9V03X.h"
#include "Pit.h"
#include "UART.h"
#include "Battery.h"
#include "Image_Process.h"
#include "Direction.h"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��


//���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��
int time_flag = 0;
int duty= 655;
void Init_All(void);

int core0_main(void)
{
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	//�û��ڴ˴����ø��ֳ�ʼ��������

    //�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);


	//ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo
    //ע�� ��V1.1.6�汾֮��  printf��ӡ����Ϣ�Ӵ�������������ѧϰ������6-Printf_Demo

	Init_All();
	ips200_showstr(0,0,"test");
	systick_delay_ms(STM0,500);

	enableInterrupts();
	while (TRUE)
	{
		//�û��ڴ˴���д�������
	    time_flag++;
	    //Servo_Control(Servo_duty);
/*	    ips200_showint32(0,3,Speed_Left,4);
	    ips200_showint32(0,4,Speed_Right,4);
	    ips200_showint32(0,5,PWM_Motor1,4);
	    ips200_showint32(0,6,PWM_Motor2,4);*/
	    if(time_flag<10)
	    {

	    }
	    else if(time_flag<20)
	    {

	    }
	    if(time_flag==200)
	    {
	        time_flag = 0;
	        Speed_Send();
	    }
	    //systick_delay_ms(STM0,100);
	    if(mt9v03x_finish_flag)
	    {
	        Get_Use_Image();
	        Get_Threshold();
	        Get_Bin_Image();
	        Find_edge1();
	        //ips200_displayimage032(Image_Bin[0],MT9V03X_W,MT9V03X_H);
	        ips200_showfloat(0, 5, Control_Error, 3, 3);
	        mt9v03x_finish_flag = 0;
	    }
	}
}

void Init_All(void)
{
    Buzzer_init();   //��������ʼ��
    ips200_init();   //��ʾ����ʼ��
    LED_Init();    //LED�Ƴ�ʼ��
    ServoMotor_init();   //�����ʼ��
    Button_init();  //������ʼ��
    Encoder_init();  //��������ʼ��
    Motor_init();   //�����ʼ��
    Bat_Volt_init();//��ѹ�ɼ�ADC��ʼ��
    uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1); //���ߴ��ڳ�ʼ��
    mt9v03x_init();  //����ͷ��ʼ��
    PIT_Speed(5);  //����5ms�ٶ��ж�
}
#pragma section all restore


