
#include "D:\arm\arm_lcd16x2_lib_test\lcd.h"
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
unsigned int minute,second,hour;
int main(void)
{
	
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
//DWT_Delay_Init();
  char s[10];	
	Lcd_Init();
	Lcd_Clear();
	int i,a;
	for(i=0;i<15;i++)
	{
    Lcd_Set_Cursor(2,i);
    Lcd_Write_Char(219);
  }
	      Lcd_Set_Cursor(1,1);
        Lcd_Write_String("LOADING...");
	while(1)
	{
        sprintf(s,"%u",(hour/10));
        Lcd_Set_Cursor(1,11);
        Lcd_Write_String(s);
        sprintf(s,"%u",(hour%10));
        Lcd_Set_Cursor(1,12);
        Lcd_Write_String(s);
        Lcd_Write_Char(37);
        HAL_Delay(10);
        hour++;
        if(hour==7)
        {
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(255);
        }
        if(hour==17)
        {
        Lcd_Set_Cursor(2,2);
        Lcd_Write_Char(255);
        }
        if(hour==24)
        {
        Lcd_Set_Cursor(2,3);
        Lcd_Write_Char(255);
        }
        if(hour==31)
        {
        Lcd_Set_Cursor(2,4);
        Lcd_Write_Char(255);
        }
        if(hour==37)
        {
        Lcd_Set_Cursor(2,5);
        Lcd_Write_Char(255);
        }
        if(hour==44)
        {
        Lcd_Set_Cursor(2,6);
        Lcd_Write_Char(255);
        }
        if(hour==51)
        {
        Lcd_Set_Cursor(2,7);
        Lcd_Write_Char(255);
        }
        if(hour==57)
        {
        Lcd_Set_Cursor(2,8);
        Lcd_Write_Char(255);
        }
        if(hour==61)
        {
        Lcd_Set_Cursor(2,9);
        Lcd_Write_Char(255);
        }
        if(hour==67)
        {
        Lcd_Set_Cursor(2,10);
        Lcd_Write_Char(255);
        }
        if(hour==74)
        {
        Lcd_Set_Cursor(2,11);
        Lcd_Write_Char(255);
        }
        if(hour==81)
        {
        Lcd_Set_Cursor(2,12);
        Lcd_Write_Char(255);
        }
        if(hour==88)
        {
        Lcd_Set_Cursor(2,13);
        Lcd_Write_Char(255);
        }
        if(hour==95)
        {
        Lcd_Set_Cursor(2,14);
        Lcd_Write_Char(255);
        }
        if(hour==100)
        {
            Lcd_Clear();
            while(hour==100)
            {
            HAL_Delay(1000);
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("  COMPLETED !!!");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("  SYSTEM READY");
            HAL_Delay(1000);
            Lcd_Clear();
            }
        }
				 HAL_Delay(100);
			}

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
