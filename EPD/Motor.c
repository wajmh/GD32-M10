#include "Motor.h"
void Clock_Motor(void){//初始化各个步进电机的时钟
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_GPIOB);
  rcu_periph_clock_enable(RCU_GPIOA);
  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10);
  gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,  GPIO_PIN_0 | GPIO_PIN_1);
	gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);	

}
void Motor_Timer2_Init(uint32_t step_hz)
{
    timer_parameter_struct t;
    timer_oc_parameter_struct oc;
    uint32_t apb1;

    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_TIMER2);

    /* STEP: PA6/PA7/PB0/PB1 -> TIMER2_CH0..CH3 */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_6 | GPIO_PIN_7);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_0 | GPIO_PIN_1);

    timer_deinit(TIMER2);
    timer_struct_para_init(&t);

    apb1 = rcu_clock_freq_get(CK_APB1);
    t.prescaler = (apb1 / 1000000U) - 1U; /* 1MHz ������׼ */
    t.period = (1000000U / step_hz) - 1U; /* step_hz = ����Ƶ�� */
    t.alignedmode = TIMER_COUNTER_EDGE;
    t.counterdirection = TIMER_COUNTER_UP;
    t.clockdivision = TIMER_CKDIV_DIV1;
        timer_init(TIMER2, &t);

    timer_channel_output_struct_para_init(&oc);
    oc.outputstate = TIMER_CCX_ENABLE;
    oc.ocpolarity = TIMER_OC_POLARITY_HIGH;

    timer_channel_output_config(TIMER2, TIMER_CH_0, &oc);
    timer_channel_output_config(TIMER2, TIMER_CH_1, &oc);
    timer_channel_output_config(TIMER2, TIMER_CH_2, &oc);
    timer_channel_output_config(TIMER2, TIMER_CH_3, &oc);

    timer_channel_output_mode_config(TIMER2, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    timer_channel_output_mode_config(TIMER2, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    timer_channel_output_mode_config(TIMER2, TIMER_CH_3, TIMER_OC_MODE_PWM0);

    uint16_t pulse = (t.period + 1U) / 2U; /* 50% ռ�ձ� */
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, pulse);
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, pulse);
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, pulse);
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, pulse);

    timer_enable(TIMER2);
}
void Motor(void)
{
//rcu_periph_clock_enable(RCU_GPIOC);
//rcu_periph_clock_enable(RCU_GPIOA);	  				     	
//// STEP
//gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);

//// EN / DIR / STEP
//gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

gpio_bit_reset(GPIOC, GPIO_PIN_0);

gpio_bit_reset(GPIOC, GPIO_PIN_2);//en
	
gpio_bit_set(GPIOC, GPIO_PIN_1);//dir
	
gpio_bit_set(GPIOA, GPIO_PIN_6);//step
	

}
void Motor1(void)
{
//rcu_periph_clock_enable(RCU_GPIOC);
//rcu_periph_clock_enable(RCU_GPIOA);	  				     	
//// STEP
//gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);

//// EN / DIR / STEP
//gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8);

gpio_bit_reset(GPIOC, GPIO_PIN_6);//sleep

gpio_bit_reset(GPIOC, GPIO_PIN_8);//en
	
gpio_bit_set(GPIOC, GPIO_PIN_7);//dir
	
gpio_bit_set(GPIOA, GPIO_PIN_7);//step
	
}
void Motor2(void)
{
//rcu_periph_clock_enable(RCU_GPIOB);
//rcu_periph_clock_enable(RCU_GPIOA);	  				     	
//// STEP
//gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0);

//// EN / DIR / STEP
//gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10);

gpio_bit_reset(GPIOA, GPIO_PIN_8);//sleep

gpio_bit_reset(GPIOA, GPIO_PIN_10);//en
	
gpio_bit_set(GPIOA, GPIO_PIN_9);//dir
	
gpio_bit_set(GPIOB, GPIO_PIN_0);//step
	
}
void Motor3(void)
{
//rcu_periph_clock_enable(RCU_GPIOC);
//rcu_periph_clock_enable(RCU_GPIOB);	  				     	
//// STEP
//gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);

//// EN / DIR / STEP
//gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

gpio_bit_reset(GPIOC, GPIO_PIN_10);//sleep

gpio_bit_reset(GPIOC, GPIO_PIN_12);//en
	
gpio_bit_set(GPIOC, GPIO_PIN_11);//dir
	
gpio_bit_set(GPIOB, GPIO_PIN_1);//step
	
}