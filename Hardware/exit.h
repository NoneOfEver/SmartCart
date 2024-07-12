#ifndef __EXTI_H
#define __EXTI_H

extern volatile uint8_t key_Num;

#define AFIO_CLK_ENABLE()               do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); }while(0)   /* AFIO时钟使能 */

#define KEY1_INT_GPIO_PORT              GPIOA
#define KEY1_INT_GPIO_PIN               GPIO_Pin_4
#define KEY1_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PA口时钟使能 */
#define KEY1_INT_IRQn                   EXTI0_IRQn
#define KEY1_INT_IRQHandler             EXTI0_IRQHandler
#define KEY1_INT_EXTI_Line              EXTI_Line0

#define KEY2_INT_GPIO_PORT              GPIOA
#define KEY2_INT_GPIO_PIN               GPIO_Pin_5
#define KEY2_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PC口时钟使能 */
#define KEY2_INT_IRQn                   EXTI1_IRQn
#define KEY2_INT_IRQHandler             EXTI1_IRQHandler
#define KEY2_INT_EXTI_Line              EXTI_Line1

#define KEY3_INT_GPIO_PORT              GPIOA
#define KEY3_INT_GPIO_PIN               GPIO_Pin_6
#define KEY3_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PC口时钟使能 */
#define KEY3_INT_IRQn                   EXTI2_IRQn
#define KEY3_INT_IRQHandler             EXTI2_IRQHandler
#define KEY3_INT_EXTI_Line              EXTI_Line2

#define KEY4_INT_GPIO_PORT              GPIOA
#define KEY4_INT_GPIO_PIN               GPIO_Pin_7
#define KEY4_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PC口时钟使能 */
#define KEY4_INT_IRQn                   EXTI3_IRQn
#define KEY4_INT_IRQHandler             EXTI3_IRQHandler
#define KEY4_INT_EXTI_Line              EXTI_Line3

#define KEY5_INT_GPIO_PORT              GPIOA
#define KEY5_INT_GPIO_PIN               GPIO_Pin_11
#define KEY5_INT_GPIO_CLK_ENABLE()      do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); }while(0)  /* PC口时钟使能 */
#define KEY5_INT_IRQn                   EXTI4_IRQn
#define KEY5_INT_IRQHandler             EXTI4_IRQHandler
#define KEY5_INT_EXTI_Line              EXTI_Line4


void KEY1_INT_IRQHandler(void);
void KEY2_INT_IRQHandler(void);
void KEY3_INT_IRQHandler(void);
void KEY4_INT_IRQHandler(void);
void KEY5_INT_IRQHandler(void);

void extix_init(void);

#endif