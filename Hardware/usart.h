#ifndef __USART_H
#define __USART_H

#include "ch32v30x.h"

#define buffer_len 256
extern volatile u8 recv_ok ;       //接收完成标志
extern u8 uart_buf[32];  //用于保存串口数据
extern volatile u8 uart_cnt ;        //用于定位串口数据的位置

void USARTx_Init(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

#endif
