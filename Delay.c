
#include "Req.h"

void TIM2_Config(void){

	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	
	//1
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	//2
	TIM2->PSC = 100 -1;		//Prescaler value
	TIM2->ARR = 0xFFFF-1;	//ARR value
	
	//3.
	TIM2->CR1 |= (1 << 0);					//Enable timer
	while(!(TIM2->SR & (1 << 0)));	// UIF: Update interrupt flag..  
																	//This bit is set by hardware when the registers are updated
}

void Delay_us(uint32_t us){

	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us, 
		 the total waiting time will be the required us delay
	************************************************/	
	TIM2->CNT = 0;
	uint32_t start = TIM2->CNT;
	while((uint32_t)(TIM2->CNT - start) < us); //In that part TIM2->CNT is 32-bit, so overflow occurs after 4294 seconds
																						//if CNT is overflowed, for example start = 0xFFFFFF00 and CNT = 0x00000050
																						//the result is 0x00000150 -> true substarct, so help with uint32_t,
																						//it automatically takes into account the overflow.
}

void Delay_ms(uint32_t ms){
	//1ms = 1000us
	uint32_t delay_ticks = ms*1000;
	uint32_t start = TIM2->CNT;
	while((uint32_t)(TIM2->CNT - start) < delay_ticks); //same application
}
