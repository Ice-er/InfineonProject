/*
 * Direction.c
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */
#include"Direction.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include "Servo_Motor.h"
#include "Motor.h"
uint16 type;
uint16 last_type;
float Error_Line = 0;
float D_Kp=2.5,D_Kd=0.008;
float Control_Error = 0;
unsigned int Left_Line[MT9V03X_H];   //左边线
unsigned int Right_Line[MT9V03X_H];  //右边线
unsigned int Center_Line[MT9V03X_H]; //中线
int Track_width[MT9V03X_H];  //赛道宽度
char Left_Findflag[MT9V03X_H] = {0};  //左线点扫描标志位
char Right_Findflag[MT9V03X_H] = {0};  //右线点扫描标志位
int break_hang = 0;   //中线断开的目标行
int Flag_s = 0;   //50行以内两边都扫到的次数
int times = 0;    //25行以内两边全丢的次数
int Leftline_duan_dian = 0;//20行以上左线突然性断裂的目标行
int Rightline_duan_dian = 0;//20行以上右线突然性断裂的目标行

void Find_Edge()
{
    int i, j;
    int old;
    for (j = 0; j < 70; j++)
    {
        for (i = old; i >= 0 && i < 184; i++)
        {
            Track_width[j]++;
            if (Image_Bin[j][i] == 0 && Image_Bin[j][i + 1] == 0 && Image_Bin[j][i + 2] == 0)
            {
                Right_Findflag[j] = 1;
                Right_Line[j] = i;   //连续两点为黑 确认右边界
                break;
            }
        }
        for (i = old; i >1 && i <= 185; i--)
        {
            Track_width[j]++;
            if (Image_Bin[j][i] == 0 && Image_Bin[j][i - 1] == 0 && Image_Bin[j][i - 2] == 0)
            {
                Left_Findflag[j] = 1;
                Left_Line[j] = i;   //连续两点为黑 确认左边界
                break;
            }
        }

        if (j <= 50 && Left_Findflag[j] == 1 && Right_Findflag[j] == 1) Flag_s++;
        if (j <= 25 && Left_Findflag[j] == 0 && Right_Findflag[j] == 0) times++;
        if (j >= 20 && (Left_Line[j] - Left_Line[j - 1]) <= -20) Leftline_duan_dian = j;
        if (j >= 20 && (Right_Line[j] - Right_Line[j - 1]) >= 20) Rightline_duan_dian = j;
        Center_Line[j] = ((Left_Line[j] + Right_Line[j]) / 2);

        if (Image_Bin[j][Center_Line[j]] == 0 && Image_Bin[j + 1][Center_Line[j]] == 0)
        {
            break_hang = j;  //提取中线为黑，说明此行中线断开
            if (break_hang >= 20)
            {
                break;  //防止20行以下break
            }
        }
        Image_Bin[j][Center_Line[j]] = 0;

        old = Center_Line[j];  //记录上一行中线位置，用于扫线起始点刷新
    }
    old = Center_Line[5];  //重置
}


void Find_edge1(void)
{
    short i,j;
    unsigned short temp =94;
    unsigned short temp1 =0;
    unsigned short temp2 =0;
    int Count_num = 0;
    float percent = 1.5;
    for(i=MT9V03X_H-1;i>30;i--)
    {
        for(j=temp;j>3;j--)   //扫左边界
        {
            if(Image_Bin[i][j]==0)
            {
                if(Image_Bin[i][j-3]==0&&Image_Bin[i][j-2]==0&&Image_Bin[i][j-1]==0)
                {
                        //Edge_left[i][j+1] = 0;
                        temp1 = j;
                        break;
                }
            }
        }

        for(j=temp;j<MT9V03X_W;j++)   //扫右边界
        {
            if(Image_Bin[i][j]==0)
            {
                if(Image_Bin[i][j+3]==0&&Image_Bin[i][j+2]==0&&Image_Bin[i][j+1]==0)
                {
                        //Edge_right[i][j] = 0;
                    temp2 = j;
                    break;
                }
            }
        }

        temp = (temp1 + temp2)/2;

        if(i>=65&&i<=75)
        {
            Error_Line += percent*(temp-MT9V03X_W/2);
            Count_num++;
            percent = percent-0.1;
        }

//        Middle_line[i] = temp;
        Image_Bin[i][temp] = 0;
    }
    Error_Line = Error_Line/Count_num;

}

void DirectionError(void)
{
    float g_fDirectionError = 0;
    static float g_fDirectionErrorTemp[5];
    float g_fDirectionError_dot;
    g_fDirectionError = Error_Line;

    g_fDirectionErrorTemp[4] = g_fDirectionErrorTemp[3];
    g_fDirectionErrorTemp[3] = g_fDirectionErrorTemp[2];
    g_fDirectionErrorTemp[2] = g_fDirectionErrorTemp[1];
    g_fDirectionErrorTemp[1] = g_fDirectionErrorTemp[0];
    g_fDirectionErrorTemp[0] = g_fDirectionError;
    g_fDirectionError_dot = 65*(g_fDirectionErrorTemp[0]-g_fDirectionErrorTemp[3]);
   // g_fDirectionError_dot = (g_fDirectionError_dot>150?150:g_fDirectionError_dot);
   // g_fDirectionError_dot = (g_fDirectionError_dot<-150?-150:g_fDirectionError_dot);

    Control_Error = D_Kp* g_fDirectionError + D_Kd* g_fDirectionError_dot;
    Control(Control_Error);
}

void Control(float x)
{
    int Servo_error;
    Servo_error = -x;
    Servo_duty = Servo_error + Servo_duty_Center;
    if(Servo_duty > Servo_max) Servo_error = Servo_max;
    if(Servo_duty < Servo_min) Servo_error = Servo_min;
    if(Flag_Stop==0)
    Servo_Control(Servo_duty);
}
