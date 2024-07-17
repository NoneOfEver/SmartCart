#ifndef __EXTI_H
#define __EXTI_H
#include "ch32v30x_exti.h"


#define AFIO_CLK_ENABLE()               do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); }while(0)   /* AFIO时钟使能 */

#define KEY1_INT_GPIO_PORT              GPIOA
#define KEY1_INT_GPIO_PIN               GPIO_Pin_4
#define KEY1_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PA口时钟使能 */
#define KEY1_INT_IRQn                   EXTI4_IRQn
#define KEY1_INT_IRQHandler             EXTI4_IRQHandler
#define KEY1_INT_EXTI_Line              EXTI_Line4

void KEY1_INT_IRQHandler(void);
void extix_init(void);

#endif