/*
 * Key_Get.h
 *
 *  Created on: 2024年5月28日
 *      Author: 宋元
 */

#ifndef USER_KEY_GET_H_
#define USER_KEY_GET_H_
extern volatile uint8_t Key_Num;
void Key_Init(void);
uint8_t Key_GetNum();

#endif /* USER_KEY_GET_H_ */
