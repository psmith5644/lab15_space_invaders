#include "timer.h"
#include <stdbool.h>
#include "TM4C123GH6PM.h" 
#include "DAC.h"
#include "sound.h"


/**
 ******************************************************************************
 * @brief   Initialize Timer2A at @freq frequency
 ******************************************************************************
 */
void Timer2A_init(uint32_t freq) {
    SYSCTL->RCGC1 |= (1 << 18); // enable clock gate control
    TIMER2->CTL &= ~(1 << 0); // disable timer
    TIMER2->CFG = 0x00000000; // 32-bit mode
    TIMER2->TAMR = 0x2; // Periodic Mode for Timer A
    TIMER2->TAPR = 0; // clock resolution: 12.5 ns
    TIMER2->TAILR = freq-1;
    TIMER2->ICR |= 0x1; // clear interrupt flag
    TIMER2->IMR |= 0x1; // enable interrupt
    
    // Sets the interrupt handler to the highest priority
    NVIC_SetPriority(TIMER2A_IRQn, 0x80000000);
    NVIC_EnableIRQ(TIMER2A_IRQn);
    
    TIMER2->CTL |= (1 << 0); // reenable timer
}

/**
 ******************************************************************************
 * @brief   When invoked, tells the sound module to output the next value
 *          of a currently playing sound to the DAC
 ******************************************************************************
 */
void Timer2A_IRQHandler(void) {
    TIMER2->ICR |= 0x1; // acknowledge interrupt
    
    // handle sound output
    Sound_output();
}