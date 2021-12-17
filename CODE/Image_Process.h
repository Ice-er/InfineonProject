/*
 * Image_Process.h
 *
 *  Created on: 2021��11��14��
 *      Author: Peng
 */

#ifndef CODE_IMAGE_PROCESS_H_
#define CODE_IMAGE_PROCESS_H_

#include "SEEKFREE_MT9V03X.h"
/** ͼ��ԭʼ���ݴ�� */
extern unsigned char Image_Use[MT9V03X_H][MT9V03X_W];

/** ��ֵ��������OLED��ʾ������ */
extern unsigned char Image_Bin[MT9V03X_H][MT9V03X_W];

extern short Threshold;
void Get_Use_Image(void);
void Get_Threshold(void);
void Get_Bin_Image (void);
short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W]);
#endif /* CODE_IMAGE_PROCESS_H_ */
