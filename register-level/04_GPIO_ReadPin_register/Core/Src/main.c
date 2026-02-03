#include "main.h"
#include "stm32f4xx.h"

int main()
{
	RCC->AHB1ENR |= (1<<0)|(1<<2);
//	RCC->AHB1ENR |= RCC->AHB1ENR_GPIOAEN | AHB1ENR_GPIOCEN ;

	GPIOA->MODER &= ~(3<<(5*2));
	GPIOA->MODER |= (1<<(5*2));

	GPIOC->MODER &= ~(3<<(13*2));

	while(1)
	{
		if(!(GPIOC->IDR &(1<<13)))
		{
			GPIOA->ODR ^= (1<<5);
		}
	}


}
