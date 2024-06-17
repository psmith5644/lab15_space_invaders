/**
 ******************************************************************************
 * @file    systick.h
 * @author  Patrick Smith
 * @brief   Functions for SysTick Interrupt
 ******************************************************************************
 *
 * Contains functions for the initialization of the SysTick Interrupt and the
 * SysTick Handler.
 *
 ******************************************************************************
 */

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stdint.h>

 
/**
 ******************************************************************************
 * @brief   Initializes the SysTick interrupt to occur at 30Hz
 ******************************************************************************
 */
void SysTick_init(void);

#endif // __SYSTICK_H__