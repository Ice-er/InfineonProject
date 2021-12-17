/*
 * Image_Process.c
 *
 *  Created on: 2021年11月14日
 *      Author: Peng
 */
#include "Image_Process.h"
/** 压缩后之后用于存放屏幕显示数据  */
unsigned char Image_Use[MT9V03X_H][MT9V03X_W];

/** 二值化后用于OLED显示的数据 */
unsigned char Image_Bin[MT9V03X_H][MT9V03X_W];

short Threshold;
void Get_Threshold()//大津法阈值
{
    Threshold = GetOSTU(Image_Use);  //大津法阈值
}
void Get_Use_Image(void)
{
    short i = 0, j = 0, row = 0, line = 0;

    for (i = 0; i < MT9V03X_H; i ++)          //神眼高 120 / 2  = 60，
    // for (i = 0; i < IMAGEH; i += 3)       //OV7725高 240 / 3  = 80，
    {
        for (j = 0; j <= MT9V03X_W; j ++)     //神眼宽188 / 2  = 94，
        // for (j = 0; j <= IMAGEW; j += 3)  //OV7725宽320 / 3  = 106，
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
    /* 二值化 */
    for (i = 0; i < MT9V03X_H; i++)
    {
        for (j = 0; j < MT9V03X_W; j++)
        {
            if (Image_Use[i][j] > Threshold) //数值越大，显示的内容越多，较浅的图像也能显示出来
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

/*大津法求阈值函数*/
short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < MT9V03X_H; j++)
    {
        for (i = 0; i < MT9V03X_W; i++)
        {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}

