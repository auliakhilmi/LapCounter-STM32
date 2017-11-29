/*
 * lcd16x2.h
 *
 *  Created on: 17 Nov 2017
 *      Author: root
 */

#ifndef LCD16X2_H_
#define LCD16X2_H_
#include "stm32f1xx_hal.h"									// tergantung jenis stm32 yang di gunakan

#define RS_Pin GPIO_PIN_0									// konfigurasi kaki PIN RS pada lcd
#define RS_GPIO_Port GPIOA									// konfigurasi PORT PIN RS pada lcd
#define EN_Pin GPIO_PIN_1									// konfigurasi kaki PIN EN pada lcd
#define EN_GPIO_Port GPIOA									// konfigurasi PORT PIN EN pada lcd
#define D4_Pin GPIO_PIN_2									// konfigurasi kaki PIN D4 pada lcd
#define D4_GPIO_Port GPIOA									// konfigurasi PORT PIN D4 pada lcd
#define D5_Pin GPIO_PIN_3									// konfigurasi kaki PIN D5 pada lcd
#define D5_GPIO_Port GPIOA									// konfigurasi PORT PIN D5 pada lcd
#define D6_Pin GPIO_PIN_4									// konfigurasi kaki PIN D6 pada lcd
#define D6_GPIO_Port GPIOA									// konfigurasi PORT PIN D6 pada lcd
#define D7_Pin GPIO_PIN_5									// konfigurasi kaki PIN D7 pada lcd
#define D7_GPIO_Port GPIOA									// konfigurasi PORT PIN D7 pada lcd

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define RS_Port GPIOA
#define EN_Port GPIOA
#define D4_Port GPIOA
#define D5_Port GPIOA
#define D6_Port GPIOA
#define D7_Port GPIOA

void LCD_Enable();
void LCD_Enable();
void LCD_Send4Bit(unsigned char Data);
void LCD_SendCommand(unsigned char command);
void LCD_Clear();
void LCD_Init();
void LCD_Gotoxy(unsigned char x,unsigned char y);
void LCD_PutChar(unsigned char Data);
void LCD_Puts(char *s);
void sPrintf(char *s,unsigned long bin);


/*		Contoh Penggunaan
 *
 * 		int d=9;
 *
 * 		sPrintf(buff,d);
	  	LCD_Gotoxy(0,0);
	  	LCD_Puts(buff);
		LCD_Gotoxy(0,1);
	  	LCD_Puts("TUGAS PROJECT");
*/

#endif /* LCD16X2_H_ */
