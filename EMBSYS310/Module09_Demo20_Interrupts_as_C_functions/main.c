#include "delay.h"
#include "stm32l475xx.h"
#include "stm32l4xx_it.h"

// LD1 --> PA5 -- Homework
// LD2 --> PB14 -- In Class

#define SYS_CLOCK_HZ 4000000u   // Default clock after startup
                                // Section 3.11 in STM32L475 datasheet DS10969

void SysTick_Initialize(void);
void Dummy_Function(void);

void main(void)
{
    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
    // RCC Base Address: 0x40021000
    // Address offset: 0x4C
    // Set bit[1] to 1
    // 1. Enable clock to Peripheral  
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // GPIOB Base Address: 0x48000400
    // Address offset: 0x00
    // Set bit[29:28] to 0x01  so --> 0x400 // To enable PB14 as output
    GPIOB->MODER &= ~GPIO_MODER_MODE14_1;
    GPIOB->MODER |= GPIO_MODER_MODE14_0;
    
    // GPIO port output data register (GPIOx_ODR) (x = A..E and H)
    // GPIOB Base Address: 0x48000400
    // Address offset: 0x14
    // Set bit[14] to 1 --> 0x4000; // Turn LED ON
    // Set bit[14] to 0 --> 0x0; // Turn LED OFF
    
    SysTick_Initialize();

    while(1)
    {
        GPIOB->ODR ^= GPIO_ODR_OD14;
        //delay(10000);
    }
}

void SysTick_Initialize(void)
{
    SysTick->LOAD = SYS_CLOCK_HZ - 1;       // 0xE000E014 - Counts down to 0.
    SysTick->VAL = 0x0;                     // 0xE000E018 - Clears initial value
    SysTick->CTRL = 0x7;                    // 0xE000E010 - Enable interrupts
}

#if 1
void SysTick_Handler(void)
{
    GPIOB->ODR ^= GPIO_ODR_OD14;
}
#endif

#if 0
void SysTick_Handler(void)
{
    __disable_irq();
    GPIOB->ODR ^= GPIO_ODR_OD14;
    __enable_irq();
}
#endif
