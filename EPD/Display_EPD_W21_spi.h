#ifndef _DISPLAY_EPD_W21_SPI_
#define _DISPLAY_EPD_W21_SPI_
#include "gd32l23x.h"


#define EPD_W21_MOSI_0	gpio_bit_reset(GPIOA, GPIO_PIN_0)
#define EPD_W21_MOSI_1	gpio_bit_set(GPIOA, GPIO_PIN_0)

#define EPD_W21_CLK_0	gpio_bit_reset(GPIOA, GPIO_PIN_1)
#define EPD_W21_CLK_1	gpio_bit_set(GPIOA, GPIO_PIN_1)

#define EPD_W21_CS_0	gpio_bit_reset(GPIOA, GPIO_PIN_4)
#define EPD_W21_CS_1	gpio_bit_set(GPIOA, GPIO_PIN_4)

#define EPD_W21_DC_0	gpio_bit_reset(GPIOB, GPIO_PIN_6)
#define EPD_W21_DC_1	gpio_bit_set(GPIOB, GPIO_PIN_6)

#define EPD_W21_RST_0	gpio_bit_reset(GPIOB, GPIO_PIN_7)
#define EPD_W21_RST_1	gpio_bit_set(GPIOB, GPIO_PIN_7)

#define isEPD_W21_BUSY gpio_input_bit_get(GPIOA, GPIO_PIN_5) // for solomen solutions


void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char datas);
void EPD_W21_WriteCMD(unsigned char command);
void EPD_GPIO_Init(void);
void Motor(void);
void Motor1(void);
void Motor2(void);
void Motor3(void);
#endif  //#ifndef _MCU_SPI_H_


