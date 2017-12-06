/*
 * LCD_HD44780.h
 *
 *  Created on: Apr 15, 2017
 *      Author: IBNU
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx_hal.h"


#define RS_Pin			GPIO_PIN_0
#define RS_GPIO_Port 	GPIOE
#define RW_Pin 			GPIO_PIN_1
#define RW_GPIO_Port 	GPIOE
#define EN_Pin 			GPIO_PIN_2
#define EN_GPIO_Port 	GPIOE
#define D4_Pin 			GPIO_PIN_3
#define D4_GPIO_Port 	GPIOE
#define D5_Pin 			GPIO_PIN_4
#define D5_GPIO_Port 	GPIOE
#define D6_Pin 			GPIO_PIN_5
#define D6_GPIO_Port 	GPIOE
#define D7_Pin 			GPIO_PIN_6
#define D7_GPIO_Port	GPIOE

/* Deklarasi Pin Control */
#define Set_En		HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
#define Clr_En		HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
#define Set_RW		HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_SET);
#define Clr_RW		HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
#define Set_RS		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
#define Clr_RS		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);

/* Global Function Here */
void LCD_Init(void);
void lcd_putchar(unsigned char c);
void lcd_putstr(char *s);
void lcd_clear(void);
void lcd_gotoxy(unsigned char col, unsigned char row);


#endif /* LCD_H_ */
