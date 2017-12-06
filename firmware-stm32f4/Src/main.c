/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "lcd.h"
#include "stdio.h"

#include "device.h"
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"


TIM_HandleTypeDef htim2;
unsigned char dis_timeout=0;
int counter_display=10;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

uint8_t readPin(GPIO_TypeDef* Port, uint16_t Pin) {
	uint8_t flag = 0;
	uint32_t Timeout_loop=0;
	uint32_t Timeout_value=0x7FFFFF;
	//unsigned char bouncing=0xFF;
	if (HAL_GPIO_ReadPin(Port, Pin) == GPIO_PIN_RESET) {
		HAL_Delay(20);
		//if (HAL_GPIO_ReadPin(Port, Pin)==GPIO_PIN_RESET){
		if(!HAL_GPIO_ReadPin(Port,Pin)) {
			while((!HAL_GPIO_ReadPin(Port,Pin))&& (Timeout_loop++<=Timeout_value));
			//while(HAL_GPIO_ReadPin(Port, Pin)==GPIO_PIN_RESET && Timeout_loop++ < Timeout_value);
			if(Timeout_loop >= Timeout_value) {
				if (Pin == GPIO_PIN_12){
					//HAL_UART_Transmit(&huart1,(uint8_t *)"Error:sensor-A\n",15,20);
				}
				else if (Pin == GPIO_PIN_13){
					dis_timeout=3;
					//HAL_UART_Transmit(&huart1,(uint8_t *)"Error:sensor-B\n",15,20);
				}
				else if (Pin == GPIO_PIN_14){
					dis_timeout=1;
					//HAL_UART_Transmit(&huart1,(uint8_t *)"Error:sensor-C\n",15,20);
				}
				else if (Pin == GPIO_PIN_15){
					dis_timeout=2;
					//HAL_UART_Transmit(&huart1,(uint8_t *)"Error:button-start\n",19,20);
				}
				else if (Pin == GPIO_PIN_11){
					//HAL_UART_Transmit(&huart1,(uint8_t *)"Error:button-reset\n",19,20);
				}
			}
			else {
				flag = 1;
			}
		}
	}
	return flag;
}

char kata[16];
int mili, det, men, lapA, lapB, lapC, mulai=0;

void TimerMulai(){
	mili++;
	if(mili==100){
		det++;
		mili = 0;
	} if(det==60){
		men++;
		det = 0;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM2){
		if(mulai==1) TimerMulai();
	}
}

void TimerReset(){
	mulai = mili = det = men = 0;
}

void CounterUpdate(uint8_t mobil) {
	switch(mobil) {
		case 1:
			lapA++;
			break;
		case 2:
			lapB++;
			break;
		case 3:
			lapC++;
			break;
	}
}

void CounterReset() {
	lapA = lapB = lapC = 0;
}

void DisplayLCD(){
	lcd_gotoxy(4,0);
	sprintf(kata,"%02d:%02d:%02d", men,det,mili);
	lcd_putstr(kata);
	lcd_gotoxy(0,1);
	sprintf(kata,"A:%02d  B:%02d  C:%02d", lapA, lapB, lapC);
	lcd_putstr(kata);
}

void DisplayTimeout(int sens){
	lcd_gotoxy(4,0);
	sprintf(kata,"%02d:%02d:%02d", men,det,mili);
	lcd_putstr(kata);
	lcd_gotoxy(0,1);
	if(sens==1){
		sprintf(kata,"TOUT  B:%02d  C:%02d", lapB, lapC);
	}else if(sens==2){
		sprintf(kata,"A:%02d  TOUT  C:%02d", lapA, lapC);
	}else{
		sprintf(kata,"A:%02d  B:%02d  TOUT", lapA, lapB);
	}
	lcd_putstr(kata);
}

void DisplayInit() {
    LCD_Init();
	lcd_gotoxy(3,0);
	lcd_putstr("Bismillah...");
	lcd_gotoxy(1,1);
	lcd_putstr("Sistem Embedded");
	HAL_Delay(1000);
	lcd_clear();
	lcd_gotoxy(1,0);
	lcd_putstr("AULIA KHILMI R");
	lcd_gotoxy(3,1);
	lcd_putstr("1110151002");
	HAL_Delay(1000);
	lcd_clear();
	DisplayLCD();
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  DisplayInit();
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
	  if(dis_timeout!=0){
		DisplayTimeout(dis_timeout);
		counter_display--;
		if(counter_display<=0){
			dis_timeout=0;
			counter_display=10;
		}
	  }else{
		  if(readPin(Sensor1_GPIO_Port, Sensor1_Pin)) {
			  if(mulai==1) CounterUpdate(2);
			  //DisplaySERIALA();
		  }
		  if(readPin(Sensor2_GPIO_Port, Sensor2_Pin)) {
			  if(mulai==1) CounterUpdate(1);
			  //DisplaySERIALB();
		  }
		  if(readPin(Sensor3_GPIO_Port, Sensor3_Pin)) {
			  if(mulai==1) CounterUpdate(3);
			  //DisplaySERIALC();
		  }
		  if(readPin(pbStart_GPIO_Port, pbStart_Pin)) {
			  mulai = !mulai;
		  }
		  if(readPin(pbReset_GPIO_Port, pbReset_Pin)) {
			  if(mulai==0){
				  TimerReset();
				  CounterReset();
			  }
		  }

		  DisplayLCD();
	  }
  }

}


static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 420;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
