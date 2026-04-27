#include "Uart.h"
#include <string.h>

#define UART_FRAME_LEN          30U
#define UART_PAYLOAD_LEN        (UART_FRAME_LEN - 2U)
#define UART_HEADER0            0x01U
#define UART_HEADER1            0x03U
#define UART_HEADER2            0x05U

static uint8_t rx_frame[UART_FRAME_LEN];
static uint8_t rx_index;
static volatile uint8_t sensor_data_ready;
static uart_sensor_data_t sensor_data;
volatile uint32_t uart_irq_count;
volatile uint32_t uart_rx_byte_count;
volatile uint32_t uart_rx_error_count;
volatile uint8_t uart_temperature_status;
volatile float uart_temperature;
volatile uint8_t uart_co_status;
volatile float uart_co;
volatile uint8_t uart_co2_status;
volatile float uart_co2;
volatile uint8_t uart_oxygen_status;
volatile float uart_oxygen;
volatile uint8_t uart_methane_status;
volatile float uart_methane;

static uint16_t crc16_modbus(const uint8_t *data, uint16_t len)
{
    uint16_t crc = 0xFFFFU;
    uint16_t i;
    uint8_t bit;

    for(i = 0U; i < len; i++) {
        crc ^= data[i];
        for(bit = 0U; bit < 8U; bit++) {
            if(crc & 0x0001U) {
                crc = (crc >> 1U) ^ 0xA001U;
            } else {
                crc >>= 1U;
            }
        }
    }

    return crc;
}

static float read_float_be(const uint8_t *data)
{
    float value;
    uint8_t bytes[4];

    bytes[0] = data[3];
    bytes[1] = data[2];
    bytes[2] = data[1];
    bytes[3] = data[0];
    memcpy(&value, bytes, sizeof(value));

    return value;
}

static void parse_sensor_frame(const uint8_t *frame)
{
    uart_sensor_data_t data;

    data.temperature_status = frame[3];
    data.temperature = read_float_be(&frame[4]);
    data.co_status = frame[8];
    data.co = read_float_be(&frame[9]);
    data.co2_status = frame[13];
    data.co2 = read_float_be(&frame[14]);
    data.oxygen_status = frame[18];
    data.oxygen = read_float_be(&frame[19]);
    data.methane_status = frame[23];
    data.methane = read_float_be(&frame[24]);

    sensor_data = data;
    uart_temperature_status = data.temperature_status;
    uart_temperature = data.temperature;
    uart_co_status = data.co_status;
    uart_co = data.co;
    uart_co2_status = data.co2_status;
    uart_co2 = data.co2;
    uart_oxygen_status = data.oxygen_status;
    uart_oxygen = data.oxygen;
    uart_methane_status = data.methane_status;
    uart_methane = data.methane;
    sensor_data_ready = 1U;
}

void usart_config(void)
{
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART1);

    /* connect port to USART1 TX */
    gpio_af_set(GPIOA, EVAL_COM_AF, GPIO_PIN_2);

    /* connect port to USART1 RX */
    gpio_af_set(GPIOA, EVAL_COM_AF, GPIO_PIN_3);

    /* configure USART TX as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_2);

    /* configure USART RX as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_3);

    /* USART configure */
    usart_deinit(USART1);
    usart_word_length_set(USART1, USART_WL_8BIT);
    usart_stop_bit_set(USART1, USART_STB_1BIT);
    usart_parity_config(USART1, USART_PM_NONE);
    usart_baudrate_set(USART1, 115200U);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    usart_enable(USART1);
    usart_interrupt_enable(USART1, USART_INT_RBNE);
    nvic_irq_enable(USART1_IRQn, 0U);
}

void usart1_receive_byte(uint8_t data)
{
    uint16_t rx_crc;
    uint16_t calc_crc;

    uart_rx_byte_count++;

    if(rx_index == 0U) {
        if(data != UART_HEADER0) {
            return;
        }
    } else if(rx_index == 1U) {
        if(data != UART_HEADER1) {
            rx_index = (data == UART_HEADER0) ? 1U : 0U;
            rx_frame[0] = data;
            return;
        }
    } else if(rx_index == 2U) {
        if(data != UART_HEADER2) {
            rx_index = 0U;
            return;
        }
    }

    rx_frame[rx_index++] = data;

    if(rx_index >= UART_FRAME_LEN) {
//        rx_crc = (uint16_t)rx_frame[UART_FRAME_LEN - 2U] |
//                 ((uint16_t)rx_frame[UART_FRAME_LEN - 1U] << 8U);
//        calc_crc = crc16_modbus(rx_frame, UART_PAYLOAD_LEN);

//        (void)rx_crc;
//        (void)calc_crc;
         parse_sensor_frame(rx_frame);

        rx_index = 0U;
    }
}

uint8_t uart_sensor_data_available(void)
{
    return sensor_data_ready;
}

uint8_t uart_sensor_data_get(uart_sensor_data_t *data)
{
    if((data == 0) || (sensor_data_ready == 0U)) {
        return 0U;
    }

    __disable_irq();
    *data = sensor_data;
    sensor_data_ready = 0U;
    __enable_irq();

    return 1U;
}

void USART1_IRQHandler(void)
{
    uart_irq_count++;

    if(RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE)) {
        usart1_receive_byte((uint8_t)usart_data_receive(USART1));
    }

    if(RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE_ORERR)) {
        uart_rx_error_count++;
        usart_interrupt_flag_clear(USART1, USART_INT_FLAG_RBNE_ORERR);
    }
}
