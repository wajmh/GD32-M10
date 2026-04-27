#ifndef _Uart_
#define _Uart_
#include "gd32l23x.h"
#define EVAL_COM_AF  GPIO_AF_7

typedef struct {
    uint8_t temperature_status;
    float temperature;
    uint8_t co_status;
    float co;
    uint8_t co2_status;
    float co2;
    uint8_t oxygen_status;
    float oxygen;
    uint8_t methane_status;
    float methane;
} uart_sensor_data_t;

void usart_config(void);
void usart1_receive_byte(uint8_t data);
uint8_t uart_sensor_data_available(void);
uint8_t uart_sensor_data_get(uart_sensor_data_t *data);
void USART1_IRQHandler(void);
#endif
