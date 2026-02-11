#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	GPIOA->MODER |= ~(3<<(5*2));
	GPIOA->MODER |= (1<<(5*2));

	TIM2->PSC = 16000 -1;
	TIM2->ARR = 1000 -1;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->CR1 = TIM_CR1_CEN;

	while(1)
	{
		if(TIM2->SR & TIM_SR_UIF)
		{
			TIM2->SR &= ~ TIM_SR_UIF;
			GPIOA->ODR ^=(1<<5);
		}
	}

}
