#include "stm32f4xx.h"

int main(void)
{
    /* Enable Clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* PA0 → Alternate Function (TIM2_CH1 AF1) */
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |=  (2 << (5 * 2));

    GPIOA->AFR[0] &= ~(0xF << (5 * 4));
    GPIOA->AFR[0] |=  (1 << (5 * 4));   // AF1 = TIM2

    /* Timer Setup */
    TIM2->PSC = 16 - 1;
    TIM2->ARR = 1000 - 1;
    TIM2->CCR1 = 0;

    TIM2->CCMR1 &= ~(7<<4);
    TIM2->CCMR1 |= (6 << 4);        // PWM Mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

    TIM2->CCER |= TIM_CCER_CC1E;
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN;

    while(1)
    {
    	for(int i = 0; i < 1000; i++)
    	        {
    	            TIM2->CCR1 = i;
    	            for(volatile int d=0; d<2000; d++);
    	        }

    	        for(int i = 1000; i > 0; i--)
    	        {
    	            TIM2->CCR1 = i;
    	            for(volatile int d=0; d<2000; d++);
    	        }
    }
}
