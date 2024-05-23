
#include "usart.h"
#include"pages.h"
#include<lcd.h>

//#define UART_BUF_SIZE 1024
u8 USART_Rbuffer_Num = 0;
u8 USART_Tbuffer_Num = 0;
u8 USART_Rbuffer[buffer_len];//接收缓冲区数组
u8 USART_Rbuffer_Camera[buffer_len];//接收缓冲区数组
u8 USART_Rbuffer_Num_Camera = 0;
//摄像头USART1，L610模块USART2,扫码器USART3，重量传感器UART4
//为了方便改动，我将定义的各种名称也是用相应的序号数字
 u8 recv_ok=0 ;       //接收完成标志
 u8 uart_buf[32]={0};  //用于保存串口数据
 u8 uart_cnt =0;        //用于定位串口数据的位置
 uint16_t received_data;

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USARTx_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure1;
    GPIO_InitTypeDef   GPIO_InitStructure2;
    GPIO_InitTypeDef   GPIO_InitStructure3;
    //GPIO_InitTypeDef   GPIO_InitStructure4;

    USART_InitTypeDef  USART_InitStructure1;
    USART_InitTypeDef  USART_InitStructure2;
    USART_InitTypeDef  USART_InitStructure3;
    //USART_InitTypeDef  USART_InitStructure4;

    NVIC_InitTypeDef   NVIC_InitStructure1;
    NVIC_InitTypeDef   NVIC_InitStructure2;
    NVIC_InitTypeDef   NVIC_InitStructure3;
    //NVIC_InitTypeDef   NVIC_InitStructure4;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  //USART1 摄像头//
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA9为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
    GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA10为浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure1);
//L610
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;              //设置PA2为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure2);
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //设置PA3为浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure2);
//扫码器
    GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //设置PB11（RX）浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure3);
//L610
    USART_InitStructure2.USART_BaudRate = 115200;
    USART_InitStructure2.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure2.USART_StopBits = USART_StopBits_1;
    USART_InitStructure2.USART_Parity = USART_Parity_No;
    USART_InitStructure2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure2.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure2);
//摄像头
    USART_InitStructure1.USART_BaudRate = 115200;
    USART_InitStructure1.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure1.USART_StopBits = USART_StopBits_1;
    USART_InitStructure1.USART_Parity = USART_Parity_No;
    USART_InitStructure1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure1.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure1);
//扫码器
    USART_InitStructure3.USART_BaudRate = 115200;
    USART_InitStructure3.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure3.USART_StopBits = USART_StopBits_1;
    USART_InitStructure3.USART_Parity = USART_Parity_No;
    USART_InitStructure3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure3.USART_Mode = USART_Mode_Rx ;
    USART_Init(USART3, &USART_InitStructure3);
//重量
//    USART_InitStructure3.USART_BaudRate = 115200;
//    USART_InitStructure3.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure3.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure3.USART_Parity = USART_Parity_No;
//    USART_InitStructure3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure3.USART_Mode = USART_Mode_Rx ;
//    USART_Init(UART4, &USART_InitStructure3);


    NVIC_InitStructure1.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为
    NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;           //子优先级为
    NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure1);                              //中断优先级初始化

    NVIC_InitStructure2.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority=2;      //抢占优先级为
    NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 2;           //子优先级为
    NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure2);                              //中断优先级初始化

    NVIC_InitStructure3.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority=1;      //抢占优先级为
    NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 1;           //子优先级为
    NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure3);                              //中断优先级初始化

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1,ENABLE);
    USART_Cmd(USART2,ENABLE);
    USART_Cmd(USART3,ENABLE);
}

void USARTx_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
    USART_SendData(pUSARTx, data);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

uint8_t USART3_ReceiveByte(void)
{
    while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
    return (uint8_t)USART_ReceiveData(USART3);
}
void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str)
{
    uint8_t i = 0;
    do
    {
       USARTx_SendByte(pUSARTx, *(str+i));
       i++;
    }while(*(str+i) != '\0');
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}
void USARTx_ReceiveStr(USART_TypeDef* pUSARTx,char *buffer)
{
   uint8_t i =0;
   char received_char=0;
   while (received_char !='\0'&&i<MAX_BUFFER_SIZE -1);

   {
       while((USART_GetITStatus(USART1, USART_IT_RXNE) != RESET));
       received_char = USART_ReceiveData(USART1);
       buffer[i] = received_char;
       i++;
   }
   buffer[i] ='\0'  ;
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
        if (received_data=='\n') // 检查是否接收到换行符
        {

            uart_cnt = 0; // 重置缓冲区计数器
            recv_ok=1;

        }
    }
}


void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //中断产生
    {
        recv_ok=2;
        USART_Rbuffer[USART_Rbuffer_Num] = USART_ReceiveData(USART2); //接收数据

        USART_Rbuffer_Num++;

        USART_ClearITPendingBit(USART2,USART_IT_RXNE);                //清除中断标志

    }

}
//void USART3_IRQHandler(void)
//{
//
//    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) // 检查接收中断
//    {
//
//            uint16_t d = USART_ReceiveData(USART3); // 接收数据
//
//            if (uart_cnt < sizeof(uart_buf) / sizeof(uart_buf[0])) // 检查缓冲区溢出
//            {
//                uart_buf[uart_cnt++] = d; // 将接收到的数据存储在缓冲区中
//            }else{
//                uart_cnt=0;
//            }
//            if (uart_cnt>=20) // 检查是否接收到换行符
//            {
//                recv_ok = 3;
//                uart_cnt = 0; // 重置缓冲区计数器
//                printf(uart_buf);
//            }
//
//            USART_ClearITPendingBit(USART3,USART_IT_RXNE); // 清除中断标志
//    }
//
//}
