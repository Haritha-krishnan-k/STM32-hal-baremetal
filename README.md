STM32 Practice (Bare Metal + HAL) 

Step 1: GPIO (Digital Output/Input) 

Goal: Control LEDs and read buttons. 

HAL Tasks: 

Toggle LED using HAL_GPIO_TogglePin. 

Blink LED with HAL_Delay. 

Read button state with HAL_GPIO_ReadPin. 

Register-Level Tasks: 

Set GPIO mode (input/output). 

Toggle output by writing ODR or using BSRR. 

Poll button input using IDR. 

Practice: Make a push-button-controlled LED. 

Step 2: External Interrupts (EXTI) 

Goal: React to events without polling. 

HAL Tasks: 

Configure button interrupt using CubeMX. 

Toggle LED in HAL_GPIO_EXTI_Callback. 

Register-Level Tasks: 

Configure EXTI line. 

Enable NVIC interrupt. 

Write ISR to toggle LED. 

Practice: Button press triggers LED blink, independent of main loop. 

Step 3: Timers 

Goal: Learn delays, periodic tasks, PWM. 

HAL Tasks: 

Timer polling mode: blink LED periodically. 

Timer interrupt mode: toggle LED in ISR. 

Timer PWM output: control LED brightness. 

Register-Level Tasks: 

Configure TIMx registers for counting. 

Enable update interrupt in DIER. 

Configure PWM output via CCRx and ARR. 

Practice: Blink LED at multiple frequencies; use PWM for dimming LED with potentiometer input. 


✅ Practice 1

Blink LED at:

200 ms

500 ms

1 second
(using only PSC and ARR)

✅ Practice 2

Button changes blink frequency:

Short press → 500 ms

Long press → 200 ms

(Hint: change ARR on the fly)

✅ Practice 3

PWM dimming:

Potentiometer → ADC

ADC value → CCR

LED brightness changes smoothly

Step 4: ADC (Analog-to-Digital Converter) 

Goal: Read analog values. 

HAL Tasks: 

Poll ADC and map values to LED brightness (PWM). 

Use ADC interrupts. 

Register-Level Tasks: 

Configure ADCx registers for single conversion. 

Read DR for ADC value. 

Practice: Control LED brightness with a potentiometer. 


Step 5: UART / USART 

Goal: Communication with PC or another MCU. 

HAL Tasks: 

Send strings via HAL_UART_Transmit. 

Receive input via HAL_UART_Receive_IT. 

Register-Level Tasks: 

Configure USARTx registers (baud, stop bits). 

Transmit & receive via DR. 

Practice: Type commands in PC terminal to toggle LEDs. 

Step 6: Combining Peripherals 

Goal: Build small interactive systems. 

Examples: 

Button + LED + UART: Press button → LED toggles → sends UART message. 

ADC + PWM + UART: Potentiometer → LED brightness → send value over UART. 

Timer + EXTI: Periodic LED blink + button interrupts. 

Step 7: Advanced Topics 

DMA (Direct Memory Access): 

ADC readings → memory buffer. 

UART transmission → buffer. 

RTC (Real-Time Clock): 

Keep time and trigger alarms. 

I2C / SPI: 

Communicate with sensors (e.g., temperature, accelerometer). 

Low-Power Modes: 

Sleep/Stop/Standby with wake-up from EXTI or RTC. 

Step 8: Mini Projects 

Idea 1: Digital thermometer (ADC + UART + display). 

Idea 2: PWM motor controller with potentiometer input. 

Idea 3: Button-controlled LED pattern generator with timer interrupts. 

Idea 4: Sensor logger: ADC → UART → PC terminal. 

 
