/*
 * peri_usart_gpu.c
 *
 *  Created on: 2015年11月23日
 *      Author: wfq
 */

#include "peri_usart_gpu.h"
#include "user_interface.h"
#include "eagle_soc.h"
#include "driver/key.h"
#include "os_type.h"
#include "mem.h"
#include "driver/uart.h"
#include "peri_dht1122.h"

static os_timer_t show_temp_timer;
static char *show_message_str;
void set_usart_gpu_content(void);

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

	if(show_message_str != NULL)
	{
		os_free(show_message_str);
		show_message_str = NULL;
	}
	show_message_str = (char *)os_malloc(length+1);
	os_memcpy(show_message_str, dat, length);
	show_message_str[length] = '\0';

	//display content
	set_usart_gpu_content();
}

void ICACHE_FLASH_ATTR
set_usart_gpu_content(void)
{
	int len,i, j,k;
	char tempbuf[6];
	char humbuf[6];
	os_memset(tempbuf,'\0',6);
	os_memset(humbuf,'\0',6);

	DHT_Sensor_Data output;
	peri_dht_read(&output);

	os_sprintf(tempbuf,"%d",(int)(output.temperature));
	os_sprintf(humbuf,"%d", (int)(output.humidity));

	j = (int)(output.temperature * 100);
	j %= 100;
	if(j  > 0)
	{
		k = os_strlen(tempbuf);
		tempbuf[k] = '.';
		os_sprintf(&tempbuf[k+1],"%d", j);
	}

	j = (int)(output.humidity * 100);
	j %= 100;
	if(j  > 0)
	{
		k = os_strlen(humbuf);
		humbuf[k] = '.';
		os_sprintf(&humbuf[k+1],"%d", j);
	}

	uart1_sendStr_no_wait("CLS(0);");

	if(show_message_str != NULL)
	{	//display content
		len = os_strlen(show_message_str);
		uart1_sendStr_no_wait("BS16(20,20,286,4,'");
		for(i=0; i<len; i++)
		{
			uart_tx_one_char_no_wait(UART1, show_message_str[i]);
		}
		uart1_sendStr_no_wait("',15);");
		PRINTF("\nRec dat len:%d,dat:%s\n", len, show_message_str);
	}

	uart1_sendStr_no_wait("PL(0,140,300,140,3);");  //display line

	//temperature  DS32(10,150,'温度：21.1℃',2);
	uart1_sendStr_no_wait("DS32(10,150,'温度：");
	uart1_sendStr_no_wait(tempbuf);
	uart1_sendStr_no_wait("℃',2);");

	//humiture  DS32(10,185,'湿度：33%',3);
	uart1_sendStr_no_wait("DS32(10,190,'湿度：");
	uart1_sendStr_no_wait(humbuf);
	uart1_sendStr_no_wait("%',4);\r\n");

	PRINTF("\nstr Temp:%s, hum:%s\n", tempbuf, humbuf);
}

void ICACHE_FLASH_ATTR
peri_usart_gpu_init(void)
{
	uart1_sendStr_no_wait("CLS(0);");
	uart1_sendStr_no_wait("CLS(0);\r\n");   //init
	uart1_sendStr_no_wait("BS16(20,35,280,4,'Hello, tisan is waiting for you!',15);");
	uart1_sendStr_no_wait("\r\n");

	os_timer_disarm(&show_temp_timer);
	os_timer_setfn(&show_temp_timer, (os_timer_func_t *)set_usart_gpu_content, NULL);
	os_timer_arm(&show_temp_timer, 15000, 1);   //call set_usart_gpu_content 15sec each
}


