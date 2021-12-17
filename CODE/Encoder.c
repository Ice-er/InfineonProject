/*
 * Encoder.c
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */
#include "Encoder.h"
void Encoder_init()
{
    gpt12_init(GPT12_T5,GPT12_T5INB_P10_3,GPT12_T5EUDB_P10_1);  //左电机
    gpt12_init(GPT12_T6,GPT12_T6INA_P20_3,GPT12_T6EUDA_P20_0);  //右电机
}

int32 Get_LeftSpeed()
{
    int32 speed;
    speed = gpt12_get(GPT12_T5);
    gpt12_clear(GPT12_T5);
    return speed;
}

int32 Get_RightSpeed()
{
    int32 speed;
    speed = gpt12_get(GPT12_T6);
    gpt12_clear(GPT12_T6);
    return speed;
}
