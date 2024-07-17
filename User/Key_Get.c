/*
 * Key_Get.c
 *
 *  Created on: 2024年5月28日
 *      Author: 宋元
 */
#include "debug.h"
#include"Key_Get.h"
volatile uint8_t Key_Num=0;
void Key_Init(void)
{
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //开启GPIOB的时钟

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_11| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_GetNum()
{

    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
       {
            Delay_Ms(20);
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0);
            Delay_Ms(20);
            Key_Num = 5;
       }

    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
       {
            Delay_Ms(20);
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0);
            Delay_Ms(20);
            Key_Num = 2;
       }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
        {
            Delay_Ms(20);
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0);
            Delay_Ms(20);
            Key_Num = 3;
        }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0)
        {
            Delay_Ms(20);
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0);
            Delay_Ms(20);
            Key_Num = 4;
        }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0)
        {
            Delay_Ms(20);
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0);
            Delay_Ms(20);
            Key_Num = 1;
        }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)
        {
            Delay_Ms(20);
            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0);
            Delay_Ms(20);
            Key_Num = 6;
        }
    return Key_Num;
}
