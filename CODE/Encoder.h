/*
 * Encoder.h
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: Peng
 */

#ifndef CODE_ENCODER_H_
#define CODE_ENCODER_H_

#include "common.h"
#include "IfxGpt12_IncrEnc.h"
#include "zf_assert.h"
#include "zf_gpt12.h"

void Encoder_init(void);
int32 Get_LeftSpeed(void);
int32 Get_RightSpeed(void);

#endif /* CODE_ENCODER_H_ */
