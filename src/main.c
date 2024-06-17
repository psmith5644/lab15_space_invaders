/**
 ******************************************************************************
 * @file    main.c
 * @author  Patrick Smith
 * @brief   Main program for a Space Invaders game, lab 15 of UTAustinX UT.6.20x
 ******************************************************************************
 *
 * The purpose of this project is to build a simple game that mimics the 
 * classic space invaders game using a TM4C123GXL Launchpad.
 * My learning objectives are to:
 * - practice creating a larger, modularized project
 * - reuse and modify modules that I created in previous labs such as...
 * - ADC with a slide potentiometer, used to control the player position;
 * - 12-bit binary DAC, used for sound;
 * - SysTick interrupts, used to control the framerate
 * - a Timer2A interrupt to output values to the DAC for 11.025kHz sounds; 
 * - use edge-triggered interrupts with buttons; 
 * - make use of LEDs and the Nokia5110 display.
 * - Improve my understanding of C and OOP by implementing polymorphic objects in C
 * and creating a game engine from scratch using OOP principles;
 * - and practice better documentation!
 ******************************************************************************
 */

#include "bsp.h"
#include "TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */
#include "DAC.h"
#include "sound.h"
#include "adc.h"
#include "PLL.h"
#include "game_engine.h"
#include "Nokia5110.h"
#include "systick.h"
#include "timer.h"


int main() {
    PLL_init();
    SysTick_init();
    Nokia5110_Init();
    ADC1_init();
    init_buttons();
    init_LEDs();
    DAC_init();
    Timer2A_init(TIMER2A_FREQ);

    __enable_irq();
    
    
    play();
}

