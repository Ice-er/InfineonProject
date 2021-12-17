/*
 * UART.h
 *
 *  Created on: 2021Äê11ÔÂ14ÈÕ
 *      Author: Peng
 */

#ifndef CODE_UART_H_
#define CODE_UART_H_

#include "common.h"

void vcan_sendware(uint8 *wareaddr,uint8 *wareaddr1,uint8 *wareaddr2,uint32 waresize,uint32 waresize1,uint32 waresize2);
void Speed_Send(void);

void UART_Task(void);
void Task1(void);
#endif /* CODE_UART_H_ */
