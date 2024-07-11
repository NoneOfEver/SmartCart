#ifndef _DMA_H_
#define _DMA_H_

#include "debug.h"
#include "ch32v30x_dma.h"
#include "stdio.h"
/* Global typedef */
typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

/* Global define */
#define TxSize1    1024
#define TxSize2    1024
/* Global Variable */
extern u8 TxBuffer1[TxSize1];  /* Send by UART2 */

extern u8 RxBuffer1[TxSize1] ;                                       /* USART2 Using  */

extern u8 TxCnt1, RxCnt1;

extern u8 Rxfinish1;

extern TestStatus TransferStatus1 ;

void DMA_INIT(void);

#endif
