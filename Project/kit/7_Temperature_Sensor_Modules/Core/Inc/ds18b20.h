#ifndef DS18B20_H
#define DS18B20_H
#define DS18B20_PORT GPIOB
#define DS18B20_PIN GPIO_PIN_0
void Timer_1us_Init(uint8_t _freq, TIM_HandleTypeDef _htim,TIM_TypeDef* _Instance) ;
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) ;
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t DS18B20_Start(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
#endif
