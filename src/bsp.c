/**
 ******************************************************************************
 * @file    bsp.c
 * @author  Patrick Smith
 * @brief   Board Support Package (BSP) for the EK-TM4C123GXL board
 ******************************************************************************
 * Includes miscellaneous functions
 ******************************************************************************
 */
 
#include "bsp.h"
#include "TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */

#define PE0 (1 << 0)
#define PE1 (1 << 1)
#define PE2 (1 << 2)
#define PE3 (1 << 3)

/**
 ******************************************************************************
 * @brief   Initialize user input buttons
 * @details Buttons are on PE0 and PE1
 ******************************************************************************
 */
void init_buttons(void) {
    SYSCTL->RCGCGPIO |= (1 << 4);
    clk_delay(3);
    GPIOE->DIR &= ~(PE0 | PE1);
    GPIOE->DEN |= (PE0 | PE1);
    GPIOE->AFSEL &= ~(PE0 | PE1);
    GPIOE->AMSEL &= ~(PE0 | PE1);
    GPIOE->PDR |= (PE0 | PE1);
    GPIOE->IS &= ~(PE0 | PE1); // enable edge-triggered interrupts
    GPIOE->IEV |= (PE0 | PE1); // interrupt on rising edge
    GPIOE->IM &= ~(PE0 | PE1); // mask the interrupt signal
}

/**
 ******************************************************************************
 * @brief   Initialize LEDs
 * @details LEDs are on PE2 (red) and PE3 (green)
 ******************************************************************************
 */
void init_LEDs(void) {
    SYSCTL->RCGCGPIO |= (1 << 4);
    clk_delay(3);
    GPIOE->DIR |= (PE2 | PE3);
    GPIOE->DEN |= (PE2 | PE3);
}

/**
 ******************************************************************************
 * @brief   read and clear the interrupt from PE0 (button 1)
 ******************************************************************************
 */
uint8_t readButton0_RIS(void) {
    uint8_t RIS_R = GPIOE->RIS;
    GPIOE->ICR |= PE0;
    return RIS_R & PE0;
}

/**
 ******************************************************************************
 * @brief   read and clear the interrupt from PE1 (button 2)
 ******************************************************************************
 */
uint8_t readButton1_RIS(void) {
    uint8_t RIS_R = GPIOE->RIS;
    GPIOE->ICR |= PE1;
    return RIS_R & PE1;
}

/**
 ******************************************************************************
 * @brief   Turn on the green LED at PE3
 ******************************************************************************
 */
void green_LED_on(void) {
    GPIOE->DATA |= PE3;
}

/**
 ******************************************************************************
 * @brief   Turn off the green LED at PE3
 ******************************************************************************
 */
void green_LED_off(void) {
    GPIOE->DATA &= ~PE3;
}

/**
 ******************************************************************************
 * @brief   Turn on the red LED at PE2
 ******************************************************************************
 */
void red_LED_on(void) {
    GPIOE->DATA |= PE2;
}

/**
 ******************************************************************************
 * @brief   Turn off the red LED at PE2
 ******************************************************************************
 */
void red_LED_off(void) {
    GPIOE->DATA &= ~PE2;
}

/**
 ******************************************************************************
 * @brief   A delay function created because some cleaner delays like 
 *          `delay = SYSCTL_RCGC2_R;` were not working, so a manual delay was 
 *          needed
 ******************************************************************************
 */
void clk_delay(uint32_t cycles) {
    for (int i = 0; i < cycles; i++) {
        // delay
    }
}

void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}
