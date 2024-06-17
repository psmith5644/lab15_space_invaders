/**
 ******************************************************************************
 * @file    adc.h
 * @author  Patrick Smith
 * @brief   Functions for ADC1
 ******************************************************************************
 *
 * Functions for Initializing and sampling from the Analog to Digital Converter
 * (ADC) on PD0.
 *
 ******************************************************************************
 */
 
#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>

#define ADC_MAX_VAL 4095

/**
 ******************************************************************************
 * @brief   Initialize ADC1 on PD0.
 ******************************************************************************
 */
void ADC1_init(void); 

/**
 ******************************************************************************
 * @brief   Takes a sample of the voltage on ADC1 (PD0)
 * @return  12-bit integer proportional to the voltage from 0-3.3V
 ******************************************************************************
 */
uint16_t ADC1_sample(void);



#endif // __ADC_H__