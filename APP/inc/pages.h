/*
 * pages.h
 *
 *  Created on: 2024年4月7日
 *      Author: noneo
 */

#ifndef USER_PAGES_H_
#define USER_PAGES_H_

#include"debug.h"
#include"stdlib.h"
//home page
/*
 * |BUTTON1|BUTTON3|
 * |BUTTON2|BUTTON4|
 *
 * */
//BUTTONs
#define BUTTON12_S_X     150
#define BUTTON12_E_X     390
#define BUTTON34_S_X     410
#define BUTTON34_E_X     650

#define BUTTON13_S_Y     110
#define BUTTON13_E_Y     260

#define BUTTON24_S_Y     290
#define BUTTON24_E_Y     440
//TEXTs
#define TEXT12_X     170
#define TEXT34_X     430
#define TEXT13_Y     170
#define TEXT24_Y     350


void renderMainPage();
void renderAddComPage();
void renderTestPage(const char* ID,const char* name,const char* priceStr,const char* weightStr);
#endif /* USER_PAGES_H_ */
