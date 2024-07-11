/********************************** (C) COPYRIGHT *******************************
* File Name          : lcd.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : This file contains the headers of the TFTLCD.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
/*
 *@Note
   FSMC routine to operate TFTLCD:
  LCD--PIN:
    PD11--FSMC_A16  cs
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

#ifndef __LCD_H
#define __LCD_H	


#include"debug.h"
#include"stdlib.h"

#define  delay_ms(x)  Delay_Ms(x)
#define  delay_us(x)  Delay_Us(x)

/* LCD parameter */
typedef struct  
{
    u16 width;
    u16 height;
    u16 id;             //LCD ID
    u8  dir;
    u16 wramcmd;
    u16 setxcmd;
    u16 setycmd;
}_lcd_dev;


extern _lcd_dev lcddev;
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;


/* LCD addr */
typedef struct
{
    vu16 LCD_REG;
    vu16 LCD_RAM;
} LCD_TypeDef;

/* A17, Bank1, sector1 */
#define LCD_BASE        ((u32)(0x60000000 | 0x0003FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

/* Scan direction definition */
#define L2R_U2D  0
#define L2R_D2U  1
#define R2L_U2D  2
#define R2L_D2U  3

#define U2D_L2R  4
#define U2D_R2L  5
#define D2U_L2R  6
#define D2U_R2L  7

#define DFT_SCAN_DIR  L2R_U2D

/* Colour */
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F//��������
#define BRED             0XF81F//������ɫ
#define GRED             0XFFE0//����
#define GBLUE            0X07FF//��ɫ
#define RED              0xF800//��ɫ

#define MAGENTA          0xF81F//��ɫ
#define GREEN            0x07E0//ǳ��ɫ
#define CYAN             0x7FFF//ǳ��ɫ
#define YELLOW           0xFFE0//ǳ��ɫ �ÿ������� ����
#define BROWN            0XBC40//΢ǳ�� �ÿ������ۣ�������Ϊ����
#define BRRED            0XFC07//��΢ǳ����һ��
#define GRAY             0X8430//���ǻ�ɫ

#define DARKBLUE         0X01CF//����ɫ
#define LIGHTBLUE        0X7D7C//��ɫ
#define GRAYBLUE         0X5458//��ɫ
 
#define LIGHTGREEN       0X841F//�Ⱥ�ɫǳһ��
#define LGRAY            0XC618//ˮ��ǽɫ

#define LGRAYBLUE        0XA651//��ݵص�ǳ��ɫ
#define LBBLUE           0X2B12//��ɫ

/*font size*/
#define BIGGER           32
#define BIGCHAR          16
#define MIDDLECHAR       12
#define SMALLCHAR        8

void LCD_Reset_GPIO_Init(void);
void LCD_Init(void);
void LCD_Clear(u16 Color);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Scan_Dir(void);
void LCD_Display_Dir(u8 dir);
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);
#endif








