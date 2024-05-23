/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/*
 *@Note

*/

#include "debug.h"
#include "usart.h"
#include <string.h>
#include "L610.h"
#include "lcd.h"
#include "pages.h"
#include <string.h>
#include <ctype.h>


/*
 *@Note
   FSMC routine to operate TFTLCD:
  LCD--PIN:
    PD11--FSMC_A16
    PD12--FSMC_A17
    PD5 --FSMC_NEW
    PD4 --FSMC_NOE
    PA15--LCDRST#
    PD14--FSMC_D0
    PD15--FSMC_D1
    PD0 --FSMC_D2
    PD1--FSMC_D3
    PE7--FSMC_D4
    PE8 --FSMC_D5
    PE9 --FSMC_D6
    PE10--FSMC_D7
    PE11--FSMC_D8
    PE12--FSMC_D9
    PE13--FSMC_D10
    PE14--FSMC_D11
    PE15--FSMC_D12
    PD8 --FSMC_D13
    PD9--FSMC_D14
    PD10--FSMC_D15
    PB14--IO_BLCTR
    PA8 --IO_MISO_NC
    PB3 --IO_MOSI_SDA
    PB15--IO_TKINT
    PC13--IO_BUSY_NC
    PC0 --IO_TKRST#
    PB4 --IO_CLK
*/



void Key_Init(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //开启GPIOA的时钟
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);                      //将PB1和PB11引脚初始化为上拉输入
}

void LCD_Reset_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_15);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10);

}
//void USART3_SendByte(uint8_t data);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_10);
    ProductInfo product;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
	Delay_Init();
    USARTx_Init();


    LCD_Reset_GPIO_Init();


    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
    Delay_Ms(100);
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
    LCD_Init();
    //LCD_Clear(GREEN);
    //POINT_COLOR=WHITE;
    //渲染主页面
    renderMainPage();

    //初始化广和通
    Delay_Ms(5000);
    L610_Init();
    L610_Lookup();
    L610_RequestIP();
    L610_SetAndConnect();
    L610_Sub();



    while(1)
    {

        if(recv_ok==1)
        {
            recv_ok=0;
            LCD_ShowString(40,100,20*BIGCHAR,32,32,"ok");
            L610_Pub((const char*)uart_buf);
            Delay_Ms(200);
            product=L610_Recive();
            LCD_ShowString(40,80,20*BIGCHAR,32,32,(u8*)product.productWeightStr);
        }
        

    }

}

