/*
 * ADC.c
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */

#include "ADC.h"
#include "stdlib.h"

uint16 ad_value[16],ad_bat,ad_stop;
uint8 AD[16];
uint16 Max[16],Min[16]={40,10,40,40,40,10,40,40,40,5,40,40,40,10,40,40},Range[16]={3300,2200,2000,2000,2000,2200,3300,2000,1800,1800,1800,1800,1800,1800,1800,1800};
//uint16 Max[16],Min[16]={40,10,40,40,40,10,40,40,40,5,40,40,40,10,40,40},Range[16]={3650,2550,2300,2300,2300,2550,3650,2000,1800,1800,1800,1800,1800,1800,1800,1800};
void Adc_init()
{
    //��ʼ��ADC  ��һ������ѡ��ģ��ţ� �ڶ�������ѡ����ʹ�õ�����
    //������Ҫע�⣬����ʹ��ģ��1 ������Ӧ����ģ��1��ѡ�������ѡ������ģ�������
    adc_init(ADC_0, ADC0_CH0_A0 );
    adc_init(ADC_0, ADC0_CH1_A1 );
    adc_init(ADC_0, ADC0_CH2_A2 );
    adc_init(ADC_0, ADC0_CH3_A3 );
    adc_init(ADC_0, ADC0_CH4_A4 );
    adc_init(ADC_0, ADC0_CH5_A5 );
    adc_init(ADC_0, ADC0_CH6_A6 );
    adc_init(ADC_0, ADC0_CH7_A7 );
    adc_init(ADC_0, ADC0_CH8_A8 );
}
void Get_Adc(uint8 mean_times)
{
    ad_value[0]  = adc_mean_filter(ADC_0, ADC0_CH0_A0 , ADC_12BIT, mean_times);
    ad_value[1]  = adc_mean_filter(ADC_0, ADC0_CH1_A1 , ADC_12BIT, mean_times);
    ad_value[2]  = adc_mean_filter(ADC_0, ADC0_CH2_A2 , ADC_12BIT, mean_times);
    ad_value[3]  = adc_mean_filter(ADC_0, ADC0_CH3_A3 , ADC_12BIT, mean_times);
    ad_value[4]  = adc_mean_filter(ADC_0, ADC0_CH4_A4 , ADC_12BIT, mean_times);
    ad_value[5]  = adc_mean_filter(ADC_0, ADC0_CH5_A5 , ADC_12BIT, mean_times);
    ad_value[6]  = adc_mean_filter(ADC_0, ADC0_CH6_A6 , ADC_12BIT, mean_times);
    ad_value[7]  = adc_mean_filter(ADC_0, ADC0_CH7_A7 , ADC_12BIT, mean_times);
    ad_value[8]  = adc_mean_filter(ADC_0, ADC0_CH8_A8 , ADC_12BIT, mean_times);
    Normalization();

}
void Normalization()//��һ��
{
    for(uint8 j=0;j<16;j++)
    {
        AD[j]=((float)(abs(ad_value[j]-Min[j]))/(float)Range[j])*100;
        if(AD[j]<=0)
        {
            AD[j]=1;
        }
        else if(AD[j]>=100)
        {
            AD[j]=100;
        }
    }
}
void quick_sort(uint16 s[], uint8 l, uint8 r)//Lin:��������
{
    if (l < r)
    {
        uint8 i = l, j = r;
        uint16 x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // ���������ҵ�һ��С��x����
                j--;
            if(i < j)
                s[i++] = s[j];

            while(i < j && s[i] < x) // ���������ҵ�һ�����ڵ���x����
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // �ݹ����
        quick_sort(s, i + 1, r);
    }
}
/*-------------------------------------------------------------------------------------------------------------*/
void Kalman_Filter(void)
{
        unsigned int f;
        static double R;
        static double Q;
        static double x_last[16];
        static double x_mid[16];
        static double x_now[16];
        static double p_last[16];
        static double p_mid[16];
        static double p_now[16];
        static double kg[16];
        for(f=0;f<16;f++)
        {
            x_mid[f]=x_last[f];
            p_mid[f]=p_last[f]+Q;
            kg[f]=p_mid[f]/(p_mid[f]+R);
            x_now[f]=x_mid[f]+kg[f]*(AD[f]-x_mid[f]);//���Ƴ�������ֵ
            p_now[f]=(1-kg[f])*p_mid[f];//����ֵ��Ӧ��covariance
            p_last[f] = p_now[f]; //����covarianceֵ
            x_last[f] = x_now[f]; //����ϵͳ״ֵ̬
        }
}
/*-------------------------------------------------------------------------------------------------------------*/
