#include "stm32f4xx.h"

volatile uint32_t press_t=0;
volatile uint32_t blink_arr=500;

int main()
{
RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN;
RCC->APB1ENR = RCC_APB1ENR_TIM2EN;

GPIOA->MODER = ~(3<<(5*2));
GPIOA->MODER =  (1<<(5*2));

GPIOC->MODER &= ~(3<<(5*2));

TIM2->PSC |= 16000 -1;
TIM2->ARR |= blink_arr -1;
TIM2->CR1 |= TIM_CR1_CEN;

while(1)
{
	if(!(GPIOC->IDR & (1<<13)))
	{
		press_t = TIM2->CNT;
		while(!(GPIOC->IDR & (1<<13)));
		uint32_t duration =TIM2->CNT - press_t;
		if(duration >1000)
		{
			blink_arr = 200;
		}
		else
		{
			blink_arr = 500;
		}
//		TIM2->ARR = blink_arr -1;
		TIM2->EGR |= TIM_EGR_UG;
		if(TIM2->SR & TIM_SR_UIF)
		{
			TIM2->SR &= ~TIM_SR_UIF;
			GPIOA->ODR ^= (1<<5);
		}

	}
}
}
