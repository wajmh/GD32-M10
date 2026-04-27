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

extern volatile uint32_t uart_irq_count;
extern volatile uint32_t uart_rx_byte_count;
extern volatile uint32_t uart_rx_error_count;
extern volatile uint8_t uart_temperature_status;
extern volatile float uart_temperature;
extern volatile uint8_t uart_co_status;
extern volatile float uart_co;
extern volatile uint8_t uart_co2_status;
extern volatile float uart_co2;
extern volatile uint8_t uart_oxygen_status;
extern volatile float uart_oxygen;
extern volatile uint8_t uart_methane_status;
extern volatile float uart_methane;

void usart_config(void);
void usart1_receive_byte(uint8_t data);
uint8_t uart_sensor_data_available(void);
uint8_t uart_sensor_data_get(uart_sensor_data_t *data);
void USART1_IRQHandler(void);
#endif
