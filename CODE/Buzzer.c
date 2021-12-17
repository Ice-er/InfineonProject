/*
 * Buzzer.c
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: Peng
 */
#include"Buzzer.h"
#include"Direction.h"
uint8 start_beep_flag;
uint8 beep_time;
uint8 Buzzer_time;
void Buzzer_init()
{
    gpio_init(BEEP_PIN, GPO, 0, PUSHPULL);
}

void Start_Buzzer()
{
    gpio_set(BEEP_PIN,1);
}
void Close_Buzzer()
{
    gpio_set(BEEP_PIN,0);
}
void Buzzer(void)
{
    if(type!=last_type)
    {
        switch(type)
        {
            case 3:Beep_10ms(20);break;
            case 4:Beep_10ms(30);break;
            case 5:Beep_10ms(50);break;
            case 6:Beep_10ms(50);break;
            default:break;
        }
    }
    last_type=type;
}

void Beep_10ms(uint8 bt)
{
    start_beep_flag=1;
    beep_time=bt;
}

