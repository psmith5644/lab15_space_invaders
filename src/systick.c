/**
 ******************************************************************************
 * @file    systick.c
 * @author  Patrick Smith
 * @brief   Functions for SysTick Interrupt
 ******************************************************************************
 *
 * Contains functions for the initialization of the SysTick Interrupt and the
 * SysTick Handler.
 *
 ******************************************************************************
 */
 
 #include "systick.h"
 #include "TM4C123GH6PM.h"
 #include "adc.h"
 #include "bsp.h"
 #include "game_engine.h"
 #include <stdbool.h>
 
 #define SYSTEM_CLOCK_FREQ 80000000
 
 
 extern bool waitForSysTick;
 uint32_t ms_elapsed;
 
/**
 ******************************************************************************
 * @brief   Initializes the SysTick interrupt to occur at 30Hz
 ******************************************************************************
 */
void SysTick_init(void) {
    SysTick->CTRL &= ~(1 << 0); // disable for initizalition
    SysTick->LOAD = SYSTEM_CLOCK_FREQ / SYSTICK_FREQ - 1;
    SysTick->VAL = 0;
    SysTick->CTRL |= 0x7; // enable with interrupts
    
    ms_elapsed = 0;
}

/**
 ******************************************************************************
 * @brief   Invoked at 30Hz: signals a binary semaphore that the game waits on,
 *          fixing the frame rate to 30Hz
 * @details Tracks elapsed time since program start, which is used to seed rand
 ******************************************************************************
 */
void SysTick_Handler(void) {
    waitForSysTick = false;
    ms_elapsed += 33;
}

