/*
 * Battery.c
 *
 *  Created on: 2021��11��13��
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
    //�ɼ�ADC����  �ɼ�10����ƽ��   �ֱ���8λ
    ad_value = adc_mean_filter(ADC_0, ADC0_CH8_A8, ADC_12BIT, 10);

    //���ݲɼ�����ADCֵ�����ѹ
    //����3300��ʾADC�ĵ�ѹΪ3.3V
    //256��ʾADCΪ8λ//lin:12λ��4096
    //*3��ʾ  (R11+R10)/R11 R10����200K  R11����100K
    //���ڲ�δʹ�ø߾��ȵĵ��裬��Ϊ���������ĵ�ѹһ�㶼����һ����ƫ�����ͨ����*3������߼�С�Ը���ƥ����ʵ��ѹ
    voltage = (ad_value*3300/4096)*3.005;//����֮��õ��ĵ�λΪmv
    return voltage;
}


