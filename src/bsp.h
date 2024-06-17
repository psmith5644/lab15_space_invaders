/**
 ******************************************************************************
 * @file    bsp.h
 * @author  Patrick Smith
 * @brief   Board Support Package (BSP) for the EK-TM4C123GXL board
 ******************************************************************************
 * Includes miscellaneous functions
 ******************************************************************************
 */
 
#ifndef __BSP_H__
#define __BSP_H__

#include <stdint.h>

/**
 ******************************************************************************
 * @brief   Initialize user input buttons
 ******************************************************************************
 */
void init_buttons(void);

/**
 ******************************************************************************
 * @brief   Initialize LEDs
 ******************************************************************************
 */
void init_LEDs(void);

/**
 ******************************************************************************
 * @brief   read and clear the interrupt from PE0 (button 1)
 ******************************************************************************
 */
uint8_t readButton0_RIS(void);

/**
 ******************************************************************************
 * @brief   read and clear the interrupt from PE1 (button 2)
 ******************************************************************************
 */
uint8_t readButton1_RIS(void);

/**
 ******************************************************************************
 * @brief   Turn on the green LED at PE3
 ******************************************************************************
 */
void green_LED_on(void);

/**
 ******************************************************************************
 * @brief   Turn off the green LED at PE3
 ******************************************************************************
 */
void green_LED_off(void);

/**
 ******************************************************************************
 * @brief   Turn on the red LED at PE2
 ******************************************************************************
 */
void red_LED_on(void);

/**
 ******************************************************************************
 * @brief   Turn off the red LED at PE2
 ******************************************************************************
 */
void red_LED_off(void);

/**
 ******************************************************************************
 * @brief   A delay function created because some cleaner delays like 
 *          `delay = SYSCTL_RCGC2_R;` were not working, so a manual delay was 
 *          needed
 ******************************************************************************
 */
void clk_delay(uint32_t cycles);

#endif // __BSP_H__
