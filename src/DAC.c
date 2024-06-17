/**
 ******************************************************************************
 * @file    DAC.c
 * @author  Patrick Smith
 * @brief   Functions for the 4-bit DAC on Port B
 ******************************************************************************
 */
 
#include "DAC.h"
#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "adc.h"
#include "sound.h"

#define NUM_DAC_OUTPUTS 16

/**
 ******************************************************************************
 * @brief   Initialize the 4-bit DAC on Port B
 * @details Uses PB0-3, where PB0 is the Least Significant Bit
 ******************************************************************************
 */
void DAC_init(void) {    
    SYSCTL->RCGCGPIO |= (1 << 1);
    uint8_t delay = SYSCTL->RCGCGPIO;
    clk_delay(3);
    GPIOB->DIR |= 0xF;
    GPIOB->DEN |= 0xF;
}

/**
 ******************************************************************************
 * @brief   Sets the 4-bit DAC on Port B equal to the @value param.
 * @param   value: 4-bit value to be output on the DAC
 ******************************************************************************
 */
void DAC_out(uint8_t value) {
    value = value % NUM_DAC_OUTPUTS; // assures all values are 0-15
    GPIOB->DATA = (GPIOB->DATA & ~0xF) | (value & 0xF);
}
