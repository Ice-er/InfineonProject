/*
 * LED.c
 *
 *  Created on: 2021Äê11ÔÂ13ÈÕ
 *      Author: Peng
 */
#include"LED.h"
void LED_Init()
{
    gpio_init(LED1, GPO, 1, PULLDOWN);
    gpio_init(LED2, GPO, 1, PULLDOWN);
    gpio_init(LED3, GPO, 1, PULLDOWN);
    gpio_init(LED4, GPO, 1, PULLDOWN);
}

void LED_Control(int x)
{
    switch(x)
    {
        case 1:gpio_toggle(LED1);break;
        case 2:gpio_toggle(LED2);break;
        case 3:gpio_toggle(LED3);break;
        case 4:gpio_toggle(LED4);break;
        default:break;
    }
}

void LED_Set(int x)
{
    switch(x)
    {
        case 1:gpio_set(LED1,0);break;
        case 2:gpio_set(LED2,0);break;
        case 3:gpio_set(LED3,0);break;
        case 4:gpio_set(LED4,0);break;
        default:break;
    }
}

void LED_Reset(int x)
{
    switch(x)
    {
        case 1:gpio_set(LED1,1);break;
        case 2:gpio_set(LED2,1);break;
        case 3:gpio_set(LED3,1);break;
        case 4:gpio_set(LED4,1);break;
        default:break;
    }
}


