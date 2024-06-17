/**
 ******************************************************************************
 * @file    sprite.h
 * @author  Patrick Smith
 * @brief   
 ******************************************************************************
 *
 * 
 ******************************************************************************
 */
 
#ifndef __SPRITE_H__
#define __SPRITE_H__
 
#include <stdint.h>
#include "game_object.h"


typedef struct {
    GameObject super;
    
    unsigned char const * bmp;
    uint8_t x_pos;
    uint8_t y_pos;
    bool bounded;
    uint8_t height;
    uint8_t width;
} Sprite;

void Sprite_ctor(Sprite * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, bool bounded);

void Sprite_moveBy(Sprite * const me, int16_t dx, int8_t dy);

void Sprite_update(Sprite * const me);

bool Sprite_checkCollision(Sprite const * const me, GameObject const * const other);

unsigned char const * Sprite_getBmp(Sprite const * const me);
uint8_t Sprite_getX(Sprite const * const me);
uint8_t Sprite_getY(Sprite const * const me);
bool Sprite_isOnScreen(Sprite const * const me);

#endif // __SPRITE_H__