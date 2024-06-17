/**
 ******************************************************************************
 * @file    bunker.h
 * @author  Patrick Smith
 * @brief   
 ******************************************************************************
 * 
 ******************************************************************************
 */
#ifndef __BARRIER_H__
#define __BARRIER_H__

#include "sprite.h"

// TODO: rename files to bunker.h/.c

typedef struct {
    Sprite super;
    
    uint8_t health;
} Bunker;

void Bunker_ctor(Bunker * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, uint8_t health);
void Bunker_update(Bunker * const me);
void Bunker_handleCollision(Bunker * const me, GameObject * const other);

#endif // __BARRIER_H__