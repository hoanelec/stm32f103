#include "matrix8x8.h"
#include "main.h"
uint16_t row[8] = { R1_Pin, R2_Pin, R3_Pin, R4_Pin, R5_Pin, R6_Pin, R7_Pin,
R8_Pin };
uint16_t col[8] = { C1_Pin, C2_Pin, C3_Pin, C4_Pin, C5_Pin, C6_Pin, C7_Pin,
C8_Pin };
//typedef struct  {uint8_t value
//uint8_t value;
//uint8_t value;
//uint8_t value;
//uint8_t value;
//uint8_t value;
//uint8_t value;
//uint8_t value}data;
uint8_t test[] = { 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81 };
unsigned int symHEX[][8] = { { 0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66 }, //A
		{ 0x78, 0x64, 0x68, 0x78, 0x64, 0x66, 0x66, 0x7C }, //B
		{ 0x3C, 0x62, 0x60, 0x60, 0x60, 0x62, 0x62, 0x3C }, //C
		{ 0x78, 0x64, 0x66, 0x66, 0x66, 0x66, 0x64, 0x78 }, //D
		{ 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x7E }, //E
		{ 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x60 }, //F
		{ 0x3C, 0x62, 0x60, 0x60, 0x66, 0x62, 0x62, 0x3C }, //G
		{ 0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x66 }, //H
		{ 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E }, //I
		{ 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1A, 0x0C }, //J
		{ 0x62, 0x64, 0x68, 0x70, 0x70, 0x68, 0x64, 0x62 }, //K
		{ 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E }, //L
		{ 0xC3, 0xE7, 0xDB, 0xDB, 0xC3, 0xC3, 0xC3, 0xC3 }, //M
		{ 0x62, 0x62, 0x52, 0x52, 0x4A, 0x4A, 0x46, 0x46 }, //N
		{ 0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C }, //O
		{ 0x7C, 0x62, 0x62, 0x7C, 0x60, 0x60, 0x60, 0x60 }, //P
		{ 0x38, 0x64, 0x64, 0x64, 0x64, 0x6C, 0x64, 0x3A }, //Q
		{ 0x7C, 0x62, 0x62, 0x7C, 0x70, 0x68, 0x64, 0x62 }, //R
		{ 0x1C, 0x22, 0x30, 0x18, 0x0C, 0x46, 0x46, 0x3C }, //S
		{ 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 }, //T
		{ 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C }, //U
		{ 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18 }, //V
		{ 0x81, 0x81, 0x81, 0x81, 0x81, 0x99, 0x99, 0x66 }, //W
		{ 0x42, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x42 }, //X
		{ 0xC3, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18 }, //Y
		{ 0x7E, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7E }, //Z
		{ 0x3C, 0x66, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C }, //0
		{ 0x18, 0x38, 0x58, 0x18, 0x18, 0x18, 0x18, 0x7E }, //1
		{ 0x3C, 0x66, 0x66, 0x0C, 0x18, 0x30, 0x7E, 0x7E }, //2
		{ 0x7E, 0x0C, 0x18, 0x3C, 0x06, 0x06, 0x46, 0x3C }, //3
		{ 0x0C, 0x18, 0x30, 0x6C, 0x6C, 0x7E, 0x0C, 0x0C }, //4
		{ 0x7E, 0x60, 0x60, 0x7C, 0x06, 0x06, 0x46, 0x3C }, //5
		{ 0x04, 0x08, 0x10, 0x38, 0x6C, 0x66, 0x66, 0x3C }, //6
		{ 0x7E, 0x46, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18 }, //7
		{ 0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x66, 0x3C }, //8
		{ 0x3C, 0x66, 0x66, 0x36, 0x1C, 0x08, 0x10, 0x20 }, //9
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // khoảng trắng
		{ 0x00, 0x66, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00 } // hình trái tim
};
void dl(uint16_t tm) {
	while (--tm)
		;
}
uint8_t rotateLeft(uint8_t n, uint8_t d) {
	/* In n<<d, last d bits are 0. To put first 3 bits of n at
	 last, do bitwise or of n<<d with n >>(INT_BITS - d) */
	return ((n << d) & 0xFF | (n >> (8 - d)));
}
uint8_t shiftRight(uint8_t byte, uint8_t bit) {
	return byte >> bit;
}
uint8_t shifLeft(uint8_t byte, uint8_t bit)
{
	return (byte<<bit)&0xff;
}
uint8_t scanLeft(uint8_t byte, uint8_t bit) {
	return (byte << bit) & 0xff;
}
void Matrix8x8_Display_Symbol(uint8_t _sym) {
	for (int r = 0; r < 8; r++) {
		HAL_GPIO_WritePin(GPIOA, row[r], GPIO_PIN_SET); //ROW 1 HIGH
		for (int c = 0; c < 8; c++) {
			uint8_t bit = (symHEX[_sym][r] >> (7 - c)) & 0x01; //EXTRACT 	MSB bit ex: symHEX = 0x18 (00011000), c = 3 => bit = 1 HIGH
			if (7 == c) // COL1(RB9) -> COL7(RB3), COL8(RA15)
				HAL_GPIO_WritePin(GPIOA, col[c], bit);
			else
				HAL_GPIO_WritePin(GPIOB, col[c], bit);
//			dl(5000);
				Delay_us(150);
			if (7 == c)
				HAL_GPIO_WritePin(GPIOA, col[c], GPIO_PIN_RESET);
			else
				HAL_GPIO_WritePin(GPIOB, col[c], GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(GPIOA, row[r], GPIO_PIN_RESET);
	}

}
void Matrix8x8_ShiftLR(uint8_t _sym)
{
		for (int mv = 7; mv >= 0; mv--) {
			for (int i = 0; i < 8; i++) {
				HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_SET); //ROW 1 HIGH
				for (int j = 0; j < 8; j++) {
					uint8_t bit = (shifLeft(symHEX[_sym][i], mv) >> (7 - j)) & 0x01;
					//uint8_t bit = (symHEX[_sym][i] >> (7 - j)) & 0x01;
					if (7 == j) // COL1(RB9) -> COL7(RB3), COL8(RA15)
						HAL_GPIO_WritePin(GPIOA, col[j], bit);
					else
						HAL_GPIO_WritePin(GPIOB, col[j], bit);
//					dl(5000);
						Delay_us(250);
					if (7 == j)
						HAL_GPIO_WritePin(GPIOA, col[j], GPIO_PIN_RESET);
					else
						HAL_GPIO_WritePin(GPIOB, col[j], GPIO_PIN_RESET);
				}
				HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_RESET); //ROW 1 HIGH
			}
		}
		for (int mv = 0; mv < 8; mv++)
						for (int i = 0; i < 8; i++) {
							HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_SET); //ROW 1 HIGH
							for (int j = 0; j < 8; j++) {
								uint8_t bit = (shiftRight(symHEX[_sym][i], mv) >> (7 - j))& 0x01;
								if (7 == j) // COL1(RB9) -> COL7(RB3), COL8(RA15)
									HAL_GPIO_WritePin(GPIOA, col[j], bit);
								else
									HAL_GPIO_WritePin(GPIOB, col[j], bit);
//								dl(5000);
									Delay_us(250);
								if (7 == j)
									HAL_GPIO_WritePin(GPIOA, col[j], GPIO_PIN_RESET);
								else
									HAL_GPIO_WritePin(GPIOB, col[j], GPIO_PIN_RESET);
							}
							HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_RESET); //ROW 1 HIGH
						}
}
void Matrix8x8_ShiftRL(uint8_t _sym) {
	for (int mv = 7; mv >= 0; mv--)
			for (int i = 0; i < 8; i++) {
				HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_SET); //ROW 1 HIGH
				for (int j = 0; j < 8; j++) {
					uint8_t bit = (shiftRight(symHEX[_sym][i], mv) >> (7 - j))& 0x01;
					if (7 == j) // COL1(RB9) -> COL7(RB3), COL8(RA15)
						HAL_GPIO_WritePin(GPIOA, col[j], bit);
					else
						HAL_GPIO_WritePin(GPIOB, col[j], bit);
					dl(5000);
					//	Delay_us(150);
					if (7 == j)
						HAL_GPIO_WritePin(GPIOA, col[j], GPIO_PIN_RESET);
					else
						HAL_GPIO_WritePin(GPIOB, col[j], GPIO_PIN_RESET);
				}
				HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_RESET); //ROW 1 HIGH
			}
	for (int mv = 0; mv < 8; mv++) {
		for (int i = 0; i < 8; i++) {
			HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_SET); //ROW 1 HIGH
			for (int j = 0; j < 8; j++) {
				uint8_t bit = (scanLeft(symHEX[_sym][i], mv) >> (7 - j)) & 0x01;
				//uint8_t bit = (symHEX[_sym][i] >> (7 - j)) & 0x01;
				if (7 == j) // COL1(RB9) -> COL7(RB3), COL8(RA15)
					HAL_GPIO_WritePin(GPIOA, col[j], bit);
				else
					HAL_GPIO_WritePin(GPIOB, col[j], bit);
				dl(5000);
				//	Delay_us(150);
				if (7 == j)
					HAL_GPIO_WritePin(GPIOA, col[j], GPIO_PIN_RESET);
				else
					HAL_GPIO_WritePin(GPIOB, col[j], GPIO_PIN_RESET);
			}
			HAL_GPIO_WritePin(GPIOA, row[i], GPIO_PIN_RESET); //ROW 1 HIGH
		}
	}


}
