/**
 ******************************************************************************
 * @file    adc.c
 * @author  Patrick Smith
 * @brief   Functions for ADC1
 ******************************************************************************
 *
 * Functions for Initializing and sampling from the Analog to Digital Converter
 * (ADC) on PD0.
 *
 ******************************************************************************
 */
 
#include "adc.h"
#include "TM4C123GH6PM.h"
#include "bsp.h"

#define PD0 (1 << 0)
#define SS3 (1 << 3)


/**
 ******************************************************************************
 * @brief   Initialize ADC1 on PD0.
 ******************************************************************************
 */
void ADC1_init(void) {
     // init PD0
    SYSCTL->RCGCGPIO |= (1 << 3);
    uint32_t delay = SYSCTL->RCGCGPIO;
    GPIOD->DIR &= ~PD0;
    GPIOD->DEN &= ~PD0;
    GPIOD->AMSEL |= PD0;
    GPIOD->AFSEL |= PD0;
    
    // enable ADC1
    SYSCTL->RCGCADC |= (1 << 1);
    delay = SYSCTL->RCGCADC;
    clk_delay(3); // delay in previous line was insufficient
    ADC1->PC = (ADC1->PC & 0xF) | 0x1; // max sample rate 125ksps 
    ADC1->SSPRI = (ADC1->SSPRI & ~0xFFFF) | 0x0123; // Prioritize SS3
    ADC1->ACTSS &= ~SS3;// disable the sample sequenceer SS3 for config
    ADC1->EMUX &= ~(0xF000);// trigger event: software 
    ADC1->SSMUX3 = (ADC1->SSMUX3 & ~0xF) | 0x7; // input source AIn7
    ADC1->SSCTL3 = (ADC1->SSCTL3 & 0xF) | 0x6; // sample control bits
    ADC1->ACTSS |= SS3; // enable SS3
}

/**
 ******************************************************************************
 * @brief   Takes a sample of the voltage on ADC1 (PD0)
 * @return  12-bit integer proportional to the voltage from 0-3.3V
 ******************************************************************************
 */
uint16_t ADC1_sample(void) {
    ADC1->PSSI |= SS3; // initiate sample
    while ((ADC1->RIS & SS3) != SS3); // poll completion flag
    uint16_t sample = ADC1->SSFIFO3 & 0xFFF; // read data from FIFO
    ADC1->ISC |= SS3; // clear interrupt status
    return sample;
}




