#include "Display_EPD_W21_spi.h"

//E-paper GPIO initialization
void EPD_GPIO_Init(void)
{
rcu_periph_clock_enable(RCU_GPIOA);
	  				     	
gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4);

gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7 | GPIO_PIN_6);

gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_5);

}




//SPI write byte
void SPI_Write(unsigned char value)
{				   			 
	unsigned char i;
  EPD_W21_CLK_0;  
	for(i=0;i<8;i++)
	{ 
		if(value&0x80)
		  EPD_W21_MOSI_1 ;
		else
		  EPD_W21_MOSI_0 ;
		EPD_W21_CLK_1;  
	  EPD_W21_CLK_0;  
		value=value<<1;
  }
}

//SPI write command
void EPD_W21_WriteCMD(unsigned char command)
{
	EPD_W21_CS_0;
	EPD_W21_DC_0;  // D/C#   0:command  1:data
	SPI_Write(command);
	EPD_W21_CS_1;
}
//SPI write data
void EPD_W21_WriteDATA(unsigned char datas)
{
	EPD_W21_CS_0;
	EPD_W21_DC_1;  // D/C#   0:command  1:data
	SPI_Write(datas);
	EPD_W21_CS_1;
}






