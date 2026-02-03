#include "main.h"
#include "stm32f4xx.h"

int main()
{
//	RCC->AHB1ENR |= RCC->AHB1ENR_GPIOAEN | RCC->AHB1ENR_GPIOCEN;

	RCC->AHB1ENR = (1<<0)|(1<<2);

	GPIOA->MODER &= ~(3<<(5*2));
	GPIOA->MODER |=  (1<<(5*2));

    // PA5 → push-pull
    GPIOA->OTYPER &= ~(1 << 5);

    // PA5 → medium speed
    GPIOA->OSPEEDR &= ~(3 << (5 * 2));
    GPIOA->OSPEEDR |=  (1 << (5 * 2));

    // PC13 → input
    GPIOC->MODER &= ~(3 << (13 * 2));

    // PC13 → pull-up
    GPIOC->PUPDR &= ~(3 << (13 * 2));
    GPIOC->PUPDR |=  (1 << (13 * 2));

	while(1)
	{
		if(!(GPIOC->IDR & (1<<13)))
		{
			GPIOA->BSRR =(1<<5);
		}
		else
		{
			GPIOA->BSRR =(1<<(5+16));
		}
		for(int volatile i =0;i<1000000;i++);
	}
}
