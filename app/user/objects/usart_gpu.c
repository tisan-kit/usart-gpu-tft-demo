/*
 * usart_gpu.c
 *
 *  Created on: 2015Äê11ÔÂ23ÈÕ
 *      Author: Administrator
 */

#include "../../pando/pando_object.h"
#include "c_types.h"
#include "user_interface.h"
#include "usart_gpu.h"
// add your own includes below
#include "../../peripheral/peri_usart_gpu.h"


struct usart_gpu {
	char* Content;
};
void ICACHE_FLASH_ATTR
usart_gpu_init() {
	// TODO: add your object init code here.
	peri_usart_gpu_init();
}
void ICACHE_FLASH_ATTR
usart_gpu_set(struct usart_gpu* value) {
	// TODO: implement object set function here.
	// the set function read value and operate the hardware.
	peri_usart_gpu_set(value->Content);

}
void ICACHE_FLASH_ATTR
usart_gpu_get(struct usart_gpu* value) {
	// TODO: implement object get  function here
	// get function retrieve hardware status and assign it to value.


}
/*
	auto generated code below!!
	DO NOT edit unless you know how it works.
*/
struct usart_gpu* ICACHE_FLASH_ATTR
create_usart_gpu() {
	struct usart_gpu* usart_gpu = (struct usart_gpu*)os_malloc(sizeof(usart_gpu));
	return usart_gpu;
}
void ICACHE_FLASH_ATTR
delete_usart_gpu(struct usart_gpu* usart_gpu) {
	if(usart_gpu){
		os_free(usart_gpu);
	}
}
void ICACHE_FLASH_ATTR
usart_gpu_object_pack(PARAMS * params) {
	if(NULL == params){
		PRINTF("Create first tlv param failed.\n");
		return;
	}

	struct usart_gpu* usart_gpu = create_usart_gpu();
	usart_gpu_get(usart_gpu);

//	if (add_next_char*(params, usart_gpu->Content)){
//		PRINTF("Add next param failed.\n");
//		return;
//	}

	delete_usart_gpu(usart_gpu);
}

void ICACHE_FLASH_ATTR
usart_gpu_object_unpack(PARAMS* params) {
	struct usart_gpu* usart_gpu = create_usart_gpu();
	uint16 length = 0;

	usart_gpu->Content = get_next_bytes(params, &length);
	usart_gpu->Content[length] = '\0';

	PRINTF("\n Rev dat length:%d, dat:%s\n", length, usart_gpu->Content);

	usart_gpu_set(usart_gpu);
	delete_usart_gpu(usart_gpu);
}
void ICACHE_FLASH_ATTR
usart_gpu_object_init() {
	usart_gpu_init();
	pando_object usart_gpu_object = {
		1,
		usart_gpu_object_pack,
		usart_gpu_object_unpack,
	};
	register_pando_object(usart_gpu_object);
}



