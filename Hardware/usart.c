#include "usart.h"
#include"pages.h"
#include<lcd.h>
#include<ctype.h>
#include"HX77.h"
#define MAX_BUFFER_SIZE 100
#define test
 volatile u8 recv_ok;       //接收完成标志
 u8 uart_buf[32]={0};  //用于保存串口数据
 volatile u8 uart_cnt =0;        //用于定位串口数据的位置
 uint16_t received_data;
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#ifdef test
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USARTx_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure1;
#ifdef test
    GPIO_InitTypeDef   GPIO_InitStructure2;
#endif

    USART_InitTypeDef  USART_InitStructure1;
#ifdef test
    USART_InitTypeDef  USART_InitStructure2;
#endif
    NVIC_InitTypeDef   NVIC_InitStructure1;
#ifdef test
    NVIC_InitTypeDef   NVIC_InitStructure2;
#endif

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
#ifdef test
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  //摄像头
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA9为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA10为浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
//L610
#ifdef test
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA2为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure2);
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA3为浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure2);
#endif
    //L610
#ifdef test
    USART_InitStructure2.USART_BaudRate = 115200;
    USART_InitStructure2.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure2.USART_StopBits = USART_StopBits_1;
    USART_InitStructure2.USART_Parity = USART_Parity_No;
    USART_InitStructure2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure2.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure2);
#endif
//摄像头
    USART_InitStructure1.USART_BaudRate = 115200;
    USART_InitStructure1.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure1.USART_StopBits = USART_StopBits_1;
    USART_InitStructure1.USART_Parity = USART_Parity_No;
    USART_InitStructure1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure1.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure1);

    NVIC_InitStructure1.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为
    NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;           //子优先级为
    NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure1);                              //中断优先级初始化
#ifdef test
    NVIC_InitStructure2.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为
    NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;           //子优先级为
    NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure2);                              //中断优先级初始化
#endif
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
#ifdef test
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
#endif

    DMA_Cmd(DMA1_Channel7, ENABLE); /* USART2 Tx */
    DMA_Cmd(DMA1_Channel6, ENABLE); /* USART2 Rx */

    USART_Cmd(USART1,ENABLE);
#ifdef test
    USART_Cmd(USART2,ENABLE);
#endif
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // 检查接收中断
       {
           USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志
           received_data = USART_ReceiveData(USART1); // 接收数据

           if(isalpha(received_data))
           {
                if (uart_cnt < sizeof(uart_buf) / sizeof(uart_buf[0])) // 检查缓冲区溢出
                {
                    uart_buf[uart_cnt++] = received_data; // 将接收到的数据存储在缓冲区中
                }
           }
           if(received_data=='\n') // 检查是否接收到换行符
           {
               uart_cnt = 0; // 重置缓冲区计数器
               recv_ok=1;
               numx =1;
               USART_Cmd(USART1,DISABLE);
           }

       }
}

#ifdef test
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //中断产生
    {

        USART_Rbuffer[USART_Rbuffer_Num++] = USART_ReceiveData(USART2); //接收数据
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);                //清除中断标志
    }
}
#endif

