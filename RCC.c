#include "Req.h"


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 100000000
  *            HCLK(Hz)                       = 100000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 4
  *            PLL_N                          = 100
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */


#include "Req.h"

#define PLL_M 	4
#define PLL_N		100
#define PLL_P		0	//2



void SysClockConfig(void){
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	1. ENABLE HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set
	********************************************************/
	
	//1
	RCC->CR |= RCC_CR_HSEON; //(1<<16)
	while(!(RCC->CR & RCC_CR_HSERDY)); //wait for the HSE to become ready (1<<17)
	
	//2
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;
	
	//3
	FLASH->ACR = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	
	//4.1 AHB
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	
	//4.2 APB1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	
	//4.3 APB2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	
	//5
	RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16) | (RCC_PLLCFGR_PLLSRC_HSE);
	
	//6
	RCC->CR |= RCC_CR_PLLON; //PLL enable 
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	//7
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));

}

