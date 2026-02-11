#include "stm32f4xx.h"

/* -------- Globals -------- */
volatile uint32_t msTicks = 0;
volatile uint32_t press_time = 0;
volatile uint8_t blinkRequest = 0;
volatile uint8_t blinkCount = 0;

/* -------- SysTick ISR (1 ms) -------- */
void SysTick_Handler(void)
{
    msTicks++;
}

/* -------- EXTI ISR -------- */
void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1 << 13))
    {
        EXTI->PR = (1 << 13);   // clear pending bit

        if (!(GPIOC->IDR & (1 << 13)))
        {
            /* Button pressed (PC13 = LOW) */
            press_time = msTicks;
        }
        else
        {
            /* Button released */
            uint32_t duration = msTicks - press_time;
            blinkCount = (duration >= 1000) ? 2 : 1;
            blinkRequest = 1;
        }
    }
}

/* -------- Delay using SysTick -------- */
void delay_ms(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}

/* -------- Main -------- */
int main(void)
{
    /* Enable GPIO clocks */
    RCC->AHB1ENR |= (1 << 0) | (1 << 2);   // GPIOA, GPIOC
    RCC->APB2ENR |= (1 << 14);             // SYSCFG

    /* PA5 → LED output */
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |=  (1 << (5 * 2));

    /* PC13 → input */
    GPIOC->MODER &= ~(3 << (13 * 2));

    /* EXTI mapping PC13 */
    SYSCFG->EXTICR[3] |= (2 << 4);   // PC13

    /* EXTI rising + falling */
    EXTI->IMR  |= (1 << 13);
    EXTI->RTSR |= (1 << 13);
    EXTI->FTSR |= (1 << 13);

    NVIC_EnableIRQ(EXTI15_10_IRQn);

    /* SysTick: 1 ms @ 16 MHz */
    SysTick->LOAD = 16000 - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = 7;   // ENABLE | TICKINT | CLKSOURCE

    while (1)
    {
        if (blinkRequest)
        {
            for (uint8_t i = 0; i < blinkCount; i++)
            {
                GPIOA->ODR ^= (1 << 5);
                delay_ms(200);
                GPIOA->ODR ^= (1 << 5);
                delay_ms(200);
            }
            blinkRequest = 0;
        }
    }
}
