
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
#include "HX77.h"
#include"ctype.h"
#include <Key_Get.h>
#include "structures.h"
#include "allshow.h" 
#define test
#define GapValue 270
float   BiaoDing=500.7;       //标定系数,根据自己的传感器调节



/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
	Delay_Init();
    USARTx_Init();  
         
    LCD_Reset_GPIO_Init();
    //LCD reset

    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
    Delay_Ms(100);
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
    LCD_Init();

    ProductInfoList productList;
    initProductList(&productList);
    weight=0;
    current_product_weight=0;
    former_weight=0;
    //初始化广和通
//    L610_Init();
//    L610_Lookup();
//    L610_RequestIP();
//    L610_SetAndConnect();
//    L610_Sub();

    //渲染主页面
    renderMainPage();

    //初始化重量传感器
    Delay_Ms(200);
    HX711_GPIO_Init();

    Delay_Ms(1);
    //初始化按键·······这里可能需要一个延时
    Key_Init();
    uint32_t pi=HX711_ReadData();
    
    while(1)
    {
        Key_Num=0;
        Key_Num=Key_GetNum();

        if(Key_Num==1)
        {
            Pages_add();
            USART_Cmd(USART1,ENABLE);
            while(numx==0)//等待进入中断
            {
            }
            if(recv_ok ==1)//进入的是摄像头
            {
                USART_Cmd(USART2,ENABLE);
                L610_Pub((const char*)uart_buf,"delete");
                Delay_Ms(2500);
                ProductInfo product = L610_Recive();
                insertProduct(&productList, product);
                if((product.productID!=0)&&(product.productName!=0)&&(product.productPriceStr!=0)&&(product.productWeightStr!=0))
                {
                    Pages_X_add(product);
                    printf("收到product：productID=%s\n", product.productID);
                    weight=HX711_ReadData();
                    while(weight>=15000000){}
                    weight=(HX711_ReadData()-pi)/GapValue;
                    if(!weight_check_add(product))
                    {
                        Pages_error();
                    }
                    former_weight=weight;
                    numx=0;

                }
                recv_ok=0;
            }
        }
        if(Key_Num==2)
        {
            Pages_delete();
            USART_Cmd(USART1,ENABLE);
            while(numx==0)//等待进入中断
            {
            }
            if(recv_ok ==1)//进入的是摄像头
            {
                USART_Cmd(USART2,ENABLE);
                L610_Pub((const char*)uart_buf,"add");
                Delay_Ms(2500);
                ProductInfo product = L610_Recive();
                deleteProduct(&productList, (const char*)product.productID);
                if((product.productID!=0)&&(product.productName!=0)&&(product.productPriceStr!=0)&&(product.productWeightStr!=0))
                {
                    Pages_X_delete(product);
                    printf("收到product：productID=%s\n", product.productID);
                    weight=HX711_ReadData();
                    while(weight>=15000000){}
                    weight=(HX711_ReadData()-pi)/GapValue;

                    if(!weight_check_delete(product))
                    {
                        Pages_error();
                    }
                    former_weight=weight;
                    numx=0;

                }
                recv_ok=0;
            }

        }
        if(Key_Num==3)
        {
            Pages_Pay();
            Key_Num=0;
            if(Key_Num==3)
            {
                renderMainPage();
            }

        }

        if(Key_Num==4)
        {
            renderCurrentProductsPage(&productList);
            if(Key_Num==3)
            {
                renderMainPage();
            }

        }
        if(Key_Num==5)
        {
            renderMainPage();
        }
    }

}

