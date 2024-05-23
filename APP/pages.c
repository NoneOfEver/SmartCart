/*
 * pages.c
 *
 *  Created on: 2024年4月7日
 *      Author: noneo
 */
#include"lcd.h"
#include"pages.h"
#include"debug.h"
#include"stdlib.h"
#include <stdio.h>



/*
 * @brief:渲染主页面
 * @param:NULL
 * @return:NULL
 */

void renderMainPage()
{
    LCD_Clear(BLACK);
    POINT_COLOR=WHITE;
    LCD_Color_Fill(40,24,760,456,GRAY);
    LCD_DrawLine(20,24,20,456);
    LCD_DrawLine(40,476,760,476);
    LCD_DrawLine(40,4,760,4);
    LCD_DrawLine(780,24,780,456);
    LCD_DrawRectangle(40,24,760,456);
    LCD_Draw_Circle(40,24,20);
    LCD_Draw_Circle(40,456,20);
    LCD_Draw_Circle(760,456,20);
    LCD_Draw_Circle(760,24,20);
    //LCD_Color_Fill(40,24,760,456,GRAY);
    LCD_ShowString(250,40,18*BIGCHAR,32,32,"SMART SHOPPINGCART");

    LCD_Color_Fill(60,166,270,286,LGRAY );
    LCD_Color_Fill(295,166,505,286,LGRAY );
    LCD_Color_Fill(530,166,740,286,LGRAY );
    LCD_Color_Fill(60,311,270,431,LGRAY );
    LCD_Color_Fill(295,311,505,431,LGRAY );
    LCD_Color_Fill(530,311,740,431,LGRAY );


    LCD_ShowString(100,200,7*BIGCHAR,32,32,"A:Add");
    LCD_ShowString(320,200,7*BIGCHAR,32,32,"B:Delete");
    LCD_ShowString(570,200,7*BIGCHAR,32,32,"C:Add");
    LCD_ShowString(600,240,7*BIGCHAR,32,32,"Fruit");
    LCD_ShowString(100,345,7*BIGCHAR,32,32,"D:Delete");
    LCD_ShowString(130,385,7*BIGCHAR,32,32,"Fruit");
    LCD_ShowString(320,345,7*BIGCHAR,32,32,"E:Back");
    LCD_ShowString(570,345,7*BIGCHAR,32,32,"F:Pay");



}
void Pages_add()
{



}
void Pages_delete()
{





}
void Pages_add_Fruite()
{





}
void Pages_detele_Fruit()
{

}
void Pages_Back()
{


}
void Pages_Pay()
{






}
/*
 *@brief:预留的添加商品页面，还没开始写
 *@param:NULL
 *@return:NULL
 */
void renderAddComPage()
{

}
/*
 *@brief:本页面为测试页面
 *@param:ID:        传入的商品对象的ID成员
 *       name:      传入的商品对象的name成员
 *       priceStr:  传入的商品对象的priceStr成员
 *       weightStr: 传入的商品对象的weightStr成员
 *@return:NULL
 */
void renderTestPage(const char* ID,const char* name,const char* priceStr,const char* weightStr)
{

    LCD_ShowString(250,72,sizeof(ID)*BIGCHAR,32,32,ID);
    LCD_ShowString(250,104,sizeof(name)*BIGCHAR,32,32,name);
    LCD_ShowString(250,136,sizeof(priceStr)*BIGCHAR,32,32,priceStr);
    LCD_ShowString(250,178,sizeof(weightStr)*BIGCHAR,32,32,weightStr);
}
