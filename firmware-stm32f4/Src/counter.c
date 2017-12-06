/*
 * counter.c
 *
 *  Created on: Nov 29, 2017
 *      Author: Zhuzu
 */

#include "counter.h"
#include "stdint.h"
#include "device.h"
#include "stm32f4xx.h"
#include "stdio.h"
uint8_t count;
//void CounterUpdate(void){
	//printf ("count:%d \n\r",count);
	//++count;
//}
void CounterZero(void){
	count=0;
	printf ("count:0 \n\r");
}
