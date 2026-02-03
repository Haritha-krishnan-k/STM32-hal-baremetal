#include "main.h"
#include "stm32f4xx.h"

int main()
{
	RCC->AHB1ENR |= (1<<0); //GPIOA is enabled

	GPIOA->MODER &= ~(3<<(5*2)); //clear the gpio moder
	GPIOA->MODER |=  (1<<(5*2)); //make it input

    while(1)
    {
    	GPIOA->ODR ^= (1<<5); // toggle them
    	for(int volatile i=0;i<10000000;i++); //debounce
    }
}
