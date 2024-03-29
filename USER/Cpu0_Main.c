/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
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
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。
int time_flag = 0;
int duty= 655;
void Init_All(void);

int core0_main(void)
{
	get_clk();//获取时钟频率  务必保留
	//用户在此处调用各种初始化函数等

    //等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);


	//注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo

	Init_All();
	ips200_showstr(0,0,"test");
	systick_delay_ms(STM0,500);

	enableInterrupts();
	while (TRUE)
	{
		//用户在此处编写任务代码
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
    Buzzer_init();   //蜂鸣器初始化
    ips200_init();   //显示屏初始化
    LED_Init();    //LED灯初始化
    ServoMotor_init();   //舵机初始化
    Button_init();  //按键初始化
    Encoder_init();  //编码器初始化
    Motor_init();   //电机初始化
    Bat_Volt_init();//电压采集ADC初始化
    uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1); //无线串口初始化
    mt9v03x_init();  //摄像头初始化
    PIT_Speed(5);  //开启5ms速度中断
}
#pragma section all restore


