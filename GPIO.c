
#include "Req.h"

RCC_TypeDef *pRCC;
GPIO_TypeDef *pGPIOA;
USART_TypeDef *pUSART2;

void gpio_uart2_init(void){
	
	pRCC = RCC;
	
	
	pGPIOA = GPIOA;
	
	pUSART2 = USART2;
	
	//1. enable the peripheral clock for the uart2 peripheral
	pRCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	//2. Configure the gpio pins for uart_tx and uart_rx functionality 
	//PA2 as TX , PA3 as RX
	
	//PA2 as USART2_TX
	//2.1 Enable the clock for the GPIOA peripheral	
	pRCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	//2.2 Change the mode of the PA2 to alternate function mode
	pGPIOA->MODER &= ~GPIO_MODER_MODER2; //First set reset state ~(0x3 << 4)
	pGPIOA->MODER |= GPIO_MODER_MODE2_1;	//Set alternate function mode (0x2 << 4)
	pGPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2; //~(0xF << 8)
	pGPIOA->AFR[0] |= (0x7 << 8); 
	
	//2.3 Enable or disable Pull-up resistor of the gpio pin if required. 
	pGPIOA->PUPDR &= ~(0x3 << 4); 
	pGPIOA->PUPDR |= (0x1 << 4);
	
	//PA3 as USART2_RX
	//2.4 Change the mode of the PA3 to alternate function mode
	pGPIOA->MODER &= ~GPIO_MODER_MODER3; 	//First set reset state ~(0x3 << 6)
	pGPIOA->MODER |= GPIO_MODER_MODE3_1;	//Set alternate function mode (0x2 << 6)
	pGPIOA->AFR[0] &= ~GPIO_AFRL_AFRL3; //~(0xF << 12)
	pGPIOA->AFR[0] |= (0x7 << 12);	//Set the alternate function7
	
	//2.5 enable the pull-up resistor
	pGPIOA->PUPDR &= ~(0x3 << 6);
	pGPIOA->PUPDR |= (0x1 << 6);
	
	//3. Configure the baudrate
	pUSART2->BRR = 0xD9;  //USARTDIV = USART_CLK/8x(2 - OVER8)x Baudrate--> Baudrate 115200, USART2_CLK = 25MHz, OVER8 =0
												//25MHz/16x115200 = 13,56 --> Mantissa = 13, Fraction = 0x56 * 16 = 9
												//Mantissa = 0xD, Fraction = 0x9---> USARTDIV = 0xD9
											
	
	//4 . configure the data width, no of stop bits , etc
	// <no configuration reqd here , we will use default values
	
	//5. Enable the TX, RX of the usart peripheral and usart peripheral
	pUSART2->CR1 |= (0x1 << 3) | (0x1 << 2) | (0x1 << 13);
	
	//@TODO: Do Interrupt part
}

void gpio_led_init(void){
	
		
	
	
	//PA5
	//1. Set the GPIOA clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	//2. Set the output mode of the GPIOA
	GPIOA->MODER &= ~(1 << 10);
	GPIOA->MODER |= (1 << 10);
	
	//3. Configure the OUTPUT Mode
	GPIOA->OTYPER &= ~(0x1 << 5);	//Output push-pull (reset state)
	GPIOA->OSPEEDR &= ~(0x3 << 10); //Speed is low 
	GPIOA->PUPDR	&= ~(0x3 << 10);
}




