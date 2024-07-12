#include "sys.h"
#include "exit.h"

volatile uint8_t key_Num=0;

void KEY1_INT_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void KEY2_INT_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void KEY3_INT_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void KEY4_INT_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void KEY5_INT_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//服务按键中断的系列代码
void KEY1_INT_IRQHandler(void)
{ 
    if(EXTI_GetITStatus(KEY1_INT_EXTI_Line)==SET)   /* 判断是否为中断线x的中断 */
    {
        Delay_Ms(20);       /* 消抖 */
        
        key_Num=1;
    }
    EXTI_ClearITPendingBit(KEY1_INT_EXTI_Line);     /* 清除LINEx上的中断标志位  */
}

void KEY2_INT_IRQHandler(void)
{ 
    if(EXTI_GetITStatus(KEY2_INT_EXTI_Line)==SET)   /* 判断是否为中断线x的中断 */
    {
        Delay_Ms(20);       /* 消抖 */
        
        key_Num=2;
    }
    EXTI_ClearITPendingBit(KEY2_INT_EXTI_Line);     /* 清除LINEx上的中断标志位  */
}

void KEY3_INT_IRQHandler(void)
{ 
    if(EXTI_GetITStatus(KEY3_INT_EXTI_Line)==SET)   /* 判断是否为中断线x的中断 */
    {
        Delay_Ms(20);       /* 消抖 */
        
        key_Num=3;
    }
    EXTI_ClearITPendingBit(KEY3_INT_EXTI_Line);     /* 清除LINEx上的中断标志位  */
}

void KEY4_INT_IRQHandler(void)
{ 
    if(EXTI_GetITStatus(KEY4_INT_EXTI_Line)==SET)   /* 判断是否为中断线x的中断 */
    {
        Delay_Ms(20);       /* 消抖 */
        
        key_Num=4;
    }
    EXTI_ClearITPendingBit(KEY4_INT_EXTI_Line);     /* 清除LINEx上的中断标志位  */
}

void KEY5_INT_IRQHandler(void)
{ 
    if(EXTI_GetITStatus(KEY5_INT_EXTI_Line)==SET)   /* 判断是否为中断线x的中断 */
    {
        Delay_Ms(20);       /* 消抖 */
        
        key_Num=1;
    }
    EXTI_ClearITPendingBit(KEY5_INT_EXTI_Line);     /* 清除LINEx上的中断标志位  */
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

    gpio_init_struct.GPIO_Pin = KEY2_INT_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;                 /* 上拉输入 */
    GPIO_Init(KEY2_INT_GPIO_PORT, &gpio_init_struct);           /* KEY2配置为下降沿触发中断 */
    
     gpio_init_struct.GPIO_Pin = KEY3_INT_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;                 /* 上拉输入 */
    GPIO_Init(KEY3_INT_GPIO_PORT, &gpio_init_struct);           /* KEY3配置为下降沿触发中断 */

     gpio_init_struct.GPIO_Pin = KEY4_INT_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;                 /* 上拉输入 */
    GPIO_Init(KEY4_INT_GPIO_PORT, &gpio_init_struct);           /* KEY4配置为下降沿触发中断 */

     gpio_init_struct.GPIO_Pin = KEY5_INT_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;                 /* 上拉输入 */
    GPIO_Init(KEY5_INT_GPIO_PORT, &gpio_init_struct);           /* KEY5配置为下降沿触发中断 */

     

     
    /* 中断线配置 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);  /* PA4 */
    exti_init_struct.EXTI_Line=KEY1_INT_EXTI_Line;              /* 开启外部中断线x */
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;           /* 配置为中断模式 */
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Falling;       /* 下降沿触发 */
    EXTI_Init(&exti_init_struct);                               /* 初始化外部中断线x */

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);  /* PA5 */
    exti_init_struct.EXTI_Line=KEY2_INT_EXTI_Line;              /* 开启外部中断线x */
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;           /* 配置为中断模式 */
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Falling;       /* 下降沿触发 */
    EXTI_Init(&exti_init_struct);                               /* 初始化外部中断线x */

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);  /* PA6 */
    exti_init_struct.EXTI_Line=KEY3_INT_EXTI_Line;              /* 开启外部中断线x */
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;           /* 配置为中断模式 */
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Rising;        /* 上升沿触发 */
    EXTI_Init(&exti_init_struct);                               /* 初始化外部中断线x */

     GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);  /* PA7 */
    exti_init_struct.EXTI_Line=KEY4_INT_EXTI_Line;              /* 开启外部中断线x */
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;           /* 配置为中断模式 */
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Rising;        /* 上升沿触发 */
    EXTI_Init(&exti_init_struct);                               /* 初始化外部中断线x */

     GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);  /* PA11 */
    exti_init_struct.EXTI_Line=KEY5_INT_EXTI_Line;              /* 开启外部中断线x */
    exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;           /* 配置为中断模式 */
    exti_init_struct.EXTI_Trigger = EXTI_Trigger_Rising;        /* 上升沿触发 */
    EXTI_Init(&exti_init_struct);                               /* 初始化外部中断线x */

     
    /* NVIC配置 */
    nvic_init_struct.NVIC_IRQChannel = KEY1_INT_EXTI_Line;;           /* 外部中断线x */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x02;  /* 抢占优先级2 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0x03;         /* 响应优先级3 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;               /* 使能中断 */
    NVIC_Init(&nvic_init_struct);

    nvic_init_struct.NVIC_IRQChannel = KEY2_INT_IRQn;           /* 外部中断线x */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x02;  /* 抢占优先级2 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0x03;         /* 响应优先级1 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;               /* 使能中断 */
    NVIC_Init(&nvic_init_struct);

    nvic_init_struct.NVIC_IRQChannel = KEY3_INT_IRQn;           /* 外部中断线x */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x02;  /* 抢占优先级2 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0x03;         /* 响应优先级0 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;               /* 使能中断 */
    NVIC_Init(&nvic_init_struct);

    nvic_init_struct.NVIC_IRQChannel = KEY4_INT_IRQn;           /* 外部中断线x */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x02;  /* 抢占优先级2 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0x03;         /* 响应优先级0 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;               /* 使能中断 */
    NVIC_Init(&nvic_init_struct);

    nvic_init_struct.NVIC_IRQChannel = KEY5_INT_IRQn;           /* 外部中断线x */
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x02;  /* 抢占优先级2 */
    nvic_init_struct.NVIC_IRQChannelSubPriority = 0x03;         /* 响应优先级0 */
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;               /* 使能中断 */
    NVIC_Init(&nvic_init_struct);

    
}