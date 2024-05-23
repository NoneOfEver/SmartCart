#ifndef __USART_H
#define __USART_H

#include "ch32v30x.h"

#define buffer_len 256
#define MAX_BUFFER_SIZE 100
extern u8 recv_ok ;       //接收完成标志
extern u8 uart_buf[32];  //用于保存串口数据
extern u8 uart_cnt ;        //用于定位串口数据的位置
extern char uart3_str[MAX_BUFFER_SIZE];
#define USART_REC_LEN           200
#define EN_USART1_RX            1
extern u8  USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;
void USARTx_Init(void);
void USARTx_SendByte(USART_TypeDef* pUSARTx, uint8_t data);
void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
#endif
