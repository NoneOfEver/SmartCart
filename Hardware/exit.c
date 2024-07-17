#include "sys.h"
#include "exit.h"

#include "Key_Get.h"

void KEY1_INT_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//服务按键中断的系列代码
void KEY1_INT_IRQHandler(void)
{ 
    if(EXTI_GetITStatus(KEY1_INT_EXTI_Line)==SET)   /* 判断是否为中断线x的中断 */
    {
        Delay_Ms(10);       /* 消抖 */
         while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0);
          Delay_Ms(10); 
        Key_Num=0;
    }
    EXTI_ClearITPendingBit(KEY1_INT_EXTI_Line);     /* 清除LINEx上的中断标志位  */
}


void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    EXTI_InitTypeDef exti_init_struct;
    NVIC_InitTypeDef nvic_init_struct;

    /* IO初始化配置 */
    AFIO_CLK_ENABLE();                      /* 开启AFIO时钟   */
    KEY1_INT_GPIO_CLK_ENABLE();             // 开启GPIOA的时钟
       
    gpio_init_struct.GPIO_Pin = KEY1_INT_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;                 /* 上拉输入 */
    GPIO_Init(KEY1_INT_GPIO_PORT, &gpio_init_struct);           /* KEY1配置为下降沿触发中断 */
  
    /* 中断线配置 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);  /* PA4 */
    exti_init_struct.EXTI_Line=KEY1_INT_EXTI_Line;              /* 开启外部中断线x */
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;           /* 配置为中断模式 */
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Falling;       /* 下降沿触发 */
    EXTI_Init(&exti_init_struct);                               /* 初始化外部中断线x */

     
    /* NVIC配置 */
    nvic_init_struct.NVIC_IRQChannel = KEY1_INT_EXTI_Line;;           /* 外部中断线x */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x02;  /* 抢占优先级2 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0x03;         /* 响应优先级3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;               /* 使能中断 */
    NVIC_Init(&nvic_init_struct);

}