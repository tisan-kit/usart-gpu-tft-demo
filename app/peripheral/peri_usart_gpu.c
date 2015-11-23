/*
 * peri_usart_gpu.c
 *
 *  Created on: 2015Äê11ÔÂ23ÈÕ
 *      Author: wfq
 */

#include "peri_usart_gpu.h"
#include "user_interface.h"
#include "eagle_soc.h"
#include "driver/key.h"
#include "os_type.h"
#include "mem.h"
#include "driver/uart.h"


uint8* ICACHE_FLASH_ATTR
peri_usart_gpu_get()
{
    uint8* dat;

    return dat;
}

void ICACHE_FLASH_ATTR
peri_usart_gpu_set(char* dat)
{
	int length = 0;
	uint16 i= 0;

	if(dat == NULL)
		return;
	length = os_strlen(dat);

	uart1_sendStr_no_wait("CLS(0);");
	uart1_sendStr_no_wait("BS16(20,20,286,4,'");

	for(i=0; i<length; i++)
	{
		uart_tx_one_char_no_wait(UART1, dat[i]);
	}
	uart1_sendStr_no_wait("',15);\r\n");
}


void ICACHE_FLASH_ATTR
peri_usart_gpu_init(void)
{
	uart1_sendStr_no_wait("CLS(0);");
	uart1_sendStr_no_wait("CLS(0);\r\n");   //init
	uart1_sendStr_no_wait("BS16(20,35,280,4,'Hello, tisan is waiting for you!',15);");
	uart1_sendStr_no_wait("\r\n");
}


