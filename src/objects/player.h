#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "sprite.h"

typedef struct {
    Sprite super;
    
    uint8_t health;
    uint8_t bombAmmo;
    int32_t msInvincible;
} Player;

void Player_ctor(Player * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, 
                 bool bounded, uint8_t health, uint8_t bombAmmo);
void Player_update(Player * const me);
uint8_t Player_addBombs(Player * const me, uint8_t quantity);
void Player_handleCollision(Player * const me, GameObject * const other);

#endif // __PLAYER_H__