/**
 ******************************************************************************
 * @file    PLL.c
 * @author  Patrick Smith
 * @brief   Functions to initialize the Phase-Lock-Loop.
 ******************************************************************************
 */
 
 #include "PLL.h"
 #include "TM4C123GH6PM.h"
 
/**
 ******************************************************************************
 * @brief   Sets system clock rate to 80MHz
 ******************************************************************************
 */
void PLL_init(void) {
    SYSCTL->RCC2 |= (1U << 31); // override RCC fields with RCC2 fields  
    SYSCTL->RCC2 |= (1U << 11); // bypass the PLL
    // set XTAL field to 10101 for 16MHz external crystal 
    SYSCTL->RCC = ((SYSCTL->RCC & ~(0x000007C0)) | (1U << 10 | 1U << 8 | 1U << 6));
    SYSCTL->RCC2 &= ~(0x7 << 4); // select main osc
    SYSCTL->RCC2 &= ~(1U << 13); // PLL power/operation normal
    SYSCTL->RCC2 |= (1U << 30); // use 400MHz PLL 
    SYSCTL->RCC2 = (SYSCTL->RCC2 & ~(0x1FC00000)) | (0x4 << 22); // set to 80MHz
    while ((SYSCTL->RIS & (1U << 6))==0){} // wait until PLL stabilizes
    SYSCTL->RCC2 &= ~(1U << 11); // clear the PLL bypass
}