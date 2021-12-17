/*
 * Direction.h
 *
 *  Created on: 2021��11��13��
 *      Author: Peng
 */

#ifndef CODE_DIRECTION_H_
#define CODE_DIRECTION_H_
#include "Platform_Types.h"
#include "Image_Process.h"
extern uint16 type,last_type;
extern float Error_Line;
extern float D_Kp,D_Kd;
extern float Control_Error;
void Find_Edge(void);
void Find_edge1(void);
void Control(float x);
void DirectionError(void);
#endif /* CODE_DIRECTION_H_ */
