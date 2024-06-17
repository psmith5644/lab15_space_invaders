/**
 ******************************************************************************
 * @file    sound.c
 * @author  Jonathan Valvano, modified by Patrick Smith
 * @brief   Sound assets based off the original Space Invaders and basic
 *          functions to play them.
 ******************************************************************************
 *  Modified by Patrick Smith January 12, 2024
 *
 *  Sound.c
 *  Runs on any computer
 *  Sound assets based off the original Space Invaders and basic
 *  functions to play them.  Copy these functions and constants
 *  into your SpaceInvaders.c for ease of sharing your game!
 *  Jonathan Valvano
 *  November 19, 2012
 ******************************************************************************
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdint.h>
/**
 ******************************************************************************
 * @brief   Plays a sound on the DAC
 * @details The call is ignored if another sound is currently playing.
 *          Sets static variables that will be used by the Sound_output func
 ******************************************************************************
 */
void Sound_Play(const unsigned char * const sound, uint16_t count);

/**
 ******************************************************************************
 * @brief   Outputs a single value to the DAC
 ******************************************************************************
 */
void Sound_output(void);

/** Functions to play specific sounds **/ 
void Sound_Shoot(void);
void Sound_Killed(void);
void Sound_Explosion(void);
void Sound_Fastinvader1(void);
void Sound_Fastinvader2(void);
void Sound_Fastinvader3(void);
void Sound_Fastinvader4(void);
void Sound_Highpitch(void);
  

#endif // __SOUND_H__