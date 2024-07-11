/*
 * sys.h
 *
 *  Created on: 2024年7月5日
 *      Author: 宋元
 */

#ifndef USER_SYS_H_
#define USER_SYS_H_
#include "ch32v30x.h"
#include "stdio.h"

/**
 * SYS_SUPPORT_OS用于定义系统文件夹是否支持OS
 * 0,不支持OS
 * 1,支持OS
 */
#define SYS_SUPPORT_OS          0

/********************************************************************************************/

void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);                   /* 切换引脚电平 */
void sys_intx_disable(void);                                                    /* 关闭所有中断 */
void sys_intx_enable(void);                                                     /* 开启所有中断 */
void sys_wfi_set(void);


#endif /* USER_SYS_H_ */
