#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "sprite.h"

typedef struct {
    Sprite super;
    
    uint8_t speed;
    Direction direction;
    Team team;
    uint8_t frameCount;
    uint8_t positionUpdateFrame;
} Missile;

void Missile_ctor(Missile * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, 
    uint8_t speed, Direction direction, Team team);
void Missile_update(Missile * const me);
void Missile_handleCollision(Missile * const me, GameObject * const other);

#endif // __MISSILE_H__