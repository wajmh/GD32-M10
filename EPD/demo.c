/*!
    \file    main.c
    \brief   running led

    \version 2023-06-27, V1.2.0, demo for GD32L23x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

//#include "gd32l23x.h"
//#include "systick.h"
////EPD
//#include "Display_EPD_W21_spi.h"
//#include "Display_EPD_W21.h"
//#include "Ap_29demo.h"
//#include "Motor.h"
//#include <stdio.h>
//#include "Uart.h"

//unsigned char BlackImage[EPD_ARRAY];//Define canvas space 

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/


//void demo(void)
//{
////	  unsigned int i;
//    systick_config();
////	  Clock_Motor();
//	  usart_config();
//	  int num = 123;
//    printf("Hello, USART! num = %d\r\n", num);
//	  Motor();
//    for(i = 0; i < 10000; i++) {
//		  gpio_bit_set(GPIOA, GPIO_PIN_6);
//		  delay_1us(100);
//		  gpio_bit_reset(GPIOA, GPIO_PIN_6);
//		  delay_1us(100);
//			if(i>5000)
//				gpio_bit_reset(GPIOC, GPIO_PIN_1);
//          }
//		gpio_bit_set(GPIOC, GPIO_PIN_2);
//	  Motor1();
//		for(i = 0; i < 10000; i++) {
//		  gpio_bit_set(GPIOA, GPIO_PIN_7);
//		  delay_1us(100);
//		  gpio_bit_reset(GPIOA, GPIO_PIN_7);
//		  delay_1us(100);
//			if(i>5000)
//				gpio_bit_reset(GPIOC, GPIO_PIN_7);
//          }
//		gpio_bit_set(GPIOC, GPIO_PIN_8);
//		Motor2();
//		for(i = 0; i < 10000; i++) {
//		  gpio_bit_set(GPIOB, GPIO_PIN_0);
//		  delay_1us(100);
//		  gpio_bit_reset(GPIOB, GPIO_PIN_0);
//		  delay_1us(100);
//			if(i>5000)
//				gpio_bit_reset(GPIOA, GPIO_PIN_9);
//          }
//		 gpio_bit_set(GPIOA, GPIO_PIN_10);
//		Motor3();
//		Motor_Timer2_Init(1000);
//		for(i = 0; i < 100000; i++) {
//		  gpio_bit_set(GPIOB, GPIO_PIN_1);
//		  delay_1ms(1);
//		  gpio_bit_reset(GPIOB, GPIO_PIN_1);
//		  delay_1ms(1);
//          }
//		  gpio_bit_set(GPIOC, GPIO_PIN_12);
    
//	  EPD_GPIO_Init();
//	  while(1){
//			printf("Hello, USART! num = %d\r\n", num);
//			delay_1ms(500);
//		EPD_HW_Init(); //Full screen update initialization.
//		EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
//		EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
//		delay_1ms(500); //Delay for 2s.							
//			/************Fast update mode(1.5s)*******************/
//		EPD_HW_Init_Fast(); //Fast update initialization.
//		EPD_WhiteScreen_ALL_Fast(gImage_2); //To display the second image using fast update.
//		EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
//		delay_1ms(500); //Delay for 2s.
		
		
		
//		}
	

//    /* enable the LED GPIO clock */
//    rcu_periph_clock_enable(RCU_GPIOA);
//    rcu_periph_clock_enable(RCU_GPIOC);
//    /* configure LED GPIO pin */
//    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_7 | GPIO_PIN_8);
//    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_7 | GPIO_PIN_8);
//    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7);
//    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
//    /* reset LED GPIO pin */
//    gpio_bit_reset(GPIOA, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_7 | GPIO_PIN_8);
//    gpio_bit_reset(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);

//    while(1) {
//        /* turn on LED1, turn off LED4 */
//        gpio_bit_set(GPIOA, GPIO_PIN_7);
//				gpio_bit_set(GPIOA, GPIO_PIN_0 );
//        gpio_bit_reset(GPIOC, GPIO_PIN_7);
//        delay_1ms(500);

//        /* turn on LED2, turn off LED1 */
//        gpio_bit_set(GPIOA, GPIO_PIN_1 );
//			  gpio_bit_set(GPIOA, GPIO_PIN_8);
//        gpio_bit_reset(GPIOA, GPIO_PIN_7);
//        delay_1ms(500);

//        /* turn on LED3, turn off LED2 */
//        gpio_bit_set(GPIOC, GPIO_PIN_6);
//        gpio_bit_reset(GPIOA, GPIO_PIN_2 );
//			  gpio_bit_reset(GPIOA, GPIO_PIN_8);
//        delay_1ms(500);

//		        gpio_bit_reset(GPIOA, GPIO_PIN_7);
//				gpio_bit_reset(GPIOA, GPIO_PIN_0 );
//        gpio_bit_reset(GPIOC, GPIO_PIN_7);
//        delay_1ms(500);

//        /* turn on LED2, turn off LED1 */
//        gpio_bit_reset(GPIOA, GPIO_PIN_1 );
//			  gpio_bit_reset(GPIOA, GPIO_PIN_8);
//        gpio_bit_reset(GPIOA, GPIO_PIN_7);
//        delay_1ms(500);

//        /* turn on LED3, turn off LED2 */
//        gpio_bit_reset(GPIOC, GPIO_PIN_6);
//        gpio_bit_set(GPIOA, GPIO_PIN_2 );
//			  gpio_bit_reset(GPIOA, GPIO_PIN_8);
//        delay_1ms(500);	
			
//        /* turn on LED4, turn off LED3 */
//        gpio_bit_set(GPIOC, GPIO_PIN_7);
//        gpio_bit_reset(GPIOC, GPIO_PIN_6);
//        delay_1ms(500);
//    }
//}
//int fputc(int ch, FILE *f)
//{
//    usart_data_transmit(USART1, (uint8_t)ch);
//    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
//    return ch;
//}
