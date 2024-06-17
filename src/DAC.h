/**
 ******************************************************************************
 * @file    DAC.h
 * @author  Patrick Smith
 * @brief   Functions for the 4-bit DAC on Port B
 ******************************************************************************
 */
 
#ifndef __DAC_H__
#define __DAC_H__

#include <stdint.h>

/**
 ******************************************************************************
 * @brief   Initialize the 4-bit DAC on Port B
 ******************************************************************************
 */
void DAC_init(void);


/**
 ******************************************************************************
 * @brief   Sets the 4-bit DAC on Port B equal to the @value param.
 * @param   value: 4-bit value to be output on the DAC
 ******************************************************************************
 */
void DAC_out(uint8_t value);

#endif // __DAC_H__