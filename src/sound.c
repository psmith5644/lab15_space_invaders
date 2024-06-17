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
 
#include "sound.h"
#include <stdbool.h>
#include "timer.h"
#include "DAC.h"

extern const unsigned char shoot[4080];
extern const unsigned char invaderkilled[3377];
extern const unsigned char explosion[2000];
extern const unsigned char fastinvader1[982];
extern const unsigned char fastinvader2[1042];
extern const unsigned char fastinvader3[1054];
extern const unsigned char fastinvader4[1098];
extern const unsigned char highpitch[1802];

static uint32_t count;
static bool isSoundPlaying;
static unsigned char * _sound;
static uint16_t _size;

/**
 ******************************************************************************
 * @brief   Plays a sound
 * @details The call is ignored if another sound is currently playing.
 *          Sets static variables that will be used by the Sound_output func
 ******************************************************************************
 */
void Sound_Play(const unsigned char * const sound, uint16_t size) {
    if (isSoundPlaying) {
        return;
    }
    _sound = (unsigned char* )sound;
    _size = size;
    count = 0;
    isSoundPlaying = true;
}

/**
 ******************************************************************************
 * @brief   Outputs a single value to the DAC
 ******************************************************************************
 */
void Sound_output() {
    if (isSoundPlaying && count < _size) {
        DAC_out(_sound[count]/17); // scale levels from [0:255] -> [0:15]
        ++count;
    }
    else {
        isSoundPlaying = false;
    }
}


/** Functions to play specific sounds **/ 

void Sound_Shoot(void){
  Sound_Play(shoot,4080);
}

void Sound_Killed(void){
  Sound_Play(invaderkilled,3377);
}

void Sound_Explosion(void){
  Sound_Play(explosion,2000);
}

void Sound_Fastinvader1(void){
  Sound_Play(fastinvader1,982);
}

void Sound_Fastinvader2(void){
  Sound_Play(fastinvader2,1042);
}

void Sound_Fastinvader3(void){
  Sound_Play(fastinvader3,1054);
}

void Sound_Fastinvader4(void){
  Sound_Play(fastinvader4,1098);
}

void Sound_Highpitch(void){
  Sound_Play(highpitch,1802);
}
