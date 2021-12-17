/*
 * Battery.c
 *
 *  Created on: 2021年11月13日
 *      Author: Peng
 */
#include "Battery.h"
#include "ADC.h"
uint16  voltage;

void Bat_Volt_init()
{
    adc_init(ADC_0, ADC0_CH8_A8);
}
uint16 Get_Bat_Volt()
{
    uint16  ad_value;
    uint16  voltage;
    //采集ADC数据  采集10次求平均   分辨率8位
    ad_value = adc_mean_filter(ADC_0, ADC0_CH8_A8, ADC_12BIT, 10);

    //根据采集到的ADC值计算电压
    //其中3300表示ADC的电压为3.3V
    //256表示ADC为8位//lin:12位，4096
    //*3表示  (R11+R10)/R11 R10等于200K  R11等于100K
    //由于并未使用高精度的电阻，因为测量出来的电压一般都会有一定的偏差，可以通过将*3增大或者减小以更加匹配真实电压
    voltage = (ad_value*3300/4096)*3.005;//计算之后得到的单位为mv
    return voltage;
}


