#include "stm32f411xe.h"
#include <stdint.h>


void SysClockConfig(void);
void gpio_uart2_init(void);
void gpio_led_init(void);
void TIM2_Config(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void usart2_send_char(char c);
char usart2_read_char(void);
void usart2_read_string(char *buffer, uint16_t max_len);
void usart2_send_string(const char *str);