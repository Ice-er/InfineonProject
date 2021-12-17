/*
 * Image_Process.c
 *
 *  Created on: 2021��11��14��
 *      Author: Peng
 */
#include "Image_Process.h"
/** ѹ����֮�����ڴ����Ļ��ʾ����  */
unsigned char Image_Use[MT9V03X_H][MT9V03X_W];

/** ��ֵ��������OLED��ʾ������ */
unsigned char Image_Bin[MT9V03X_H][MT9V03X_W];

short Threshold;
void Get_Threshold()//�����ֵ
{
    Threshold = GetOSTU(Image_Use);  //�����ֵ
}
void Get_Use_Image(void)
{
    short i = 0, j = 0, row = 0, line = 0;

    for (i = 0; i < MT9V03X_H; i ++)          //���۸� 120 / 2  = 60��
    // for (i = 0; i < IMAGEH; i += 3)       //OV7725�� 240 / 3  = 80��
    {
        for (j = 0; j <= MT9V03X_W; j ++)     //���ۿ�188 / 2  = 94��
        // for (j = 0; j <= IMAGEW; j += 3)  //OV7725��320 / 3  = 106��
        {
            Image_Use[row][line] = mt9v03x_image[i][j];
            line++;
        }
        line = 0;
        row++;
    }
}
void Get_Bin_Image ()
{
    unsigned short i = 0, j = 0;
    /* ��ֵ�� */
    for (i = 0; i < MT9V03X_H; i++)
    {
        for (j = 0; j < MT9V03X_W; j++)
        {
            if (Image_Use[i][j] > Threshold) //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
                Image_Bin[i][j] = 255;
            else
                Image_Bin[i][j] = 0;
        }
    }
    for (i = 0; i < MT9V03X_H; i++)
    {
        for (j = 0; j < 4; j++)
        {
            Image_Bin[i][j] = 0;
        }
        for (j = MT9V03X_W - 4; j < MT9V03X_W; j++)
        {
            Image_Bin[i][j] = 0;
        }
    }
}

/*�������ֵ����*/
short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for (j = 0; j < MT9V03X_H; j++)
    {
        for (i = 0; i < MT9V03X_W; i++)
        {
            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
        return MaxValue;         // ͼ����ֻ��һ����ɫ
    if (MinValue + 1 == MaxValue)
        return MinValue;        // ͼ����ֻ�ж�����ɫ

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  ��������

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
        PixelFore = Amount - PixelBack;           //�������ص���
        OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
        OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
        PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
        MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
        MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}

