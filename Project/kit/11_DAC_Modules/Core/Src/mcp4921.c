#include "mcp4921.h"
void SPI_Soft_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, SCLK_soft_Pin|MOSI_soft_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(SS_soft_GPIO_Port, SS_soft_Pin, GPIO_PIN_SET);

	  /*Configure GPIO pin : PC13 */
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : SCLK_soft_Pin MOSI_soft_Pin SS_soft_Pin */
	  GPIO_InitStruct.Pin = SCLK_soft_Pin|MOSI_soft_Pin|SS_soft_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void MCP4921_SPI_Soft_Send(uint16_t adc_val)
{
	if(adc_val>=0 && adc_val<4095)
	{
		HAL_GPIO_WritePin(SS_soft_GPIO_Port, SS_soft_Pin, GPIO_PIN_RESET);
			uint8_t configbits = 0x03;//Write to DACa , Unbuffered, 1x, Output power down control bit
			for(int i= 0; i<4;i++)
			{
				HAL_GPIO_WritePin(MOSI_soft_GPIO_Port, MOSI_soft_Pin, (configbits>>(4-i))&0x01);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SCLK_soft_GPIO_Port, SCLK_soft_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SCLK_soft_GPIO_Port, SCLK_soft_Pin, GPIO_PIN_RESET);
			}
			for(int i = 0;i<12;i++)
			{
				  HAL_GPIO_WritePin(MOSI_soft_GPIO_Port, MOSI_soft_Pin, (adc_val>>(12-i))&0x01);
					HAL_Delay(1);
						HAL_GPIO_WritePin(SCLK_soft_GPIO_Port, SCLK_soft_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(SCLK_soft_GPIO_Port, SCLK_soft_Pin, GPIO_PIN_RESET);
			}
			HAL_GPIO_WritePin(SS_soft_GPIO_Port, SS_soft_Pin, GPIO_PIN_SET);
	}

}
