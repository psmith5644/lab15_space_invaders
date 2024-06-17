/**
 ******************************************************************************
 * @file    enemy.h
 * @author  Patrick Smith
 * @brief   Code for an Enemy object which inherits from Sprite
 ******************************************************************************
 * Contains the intializer function, update and handleCollision virtual 
 * functions for the Enemy object
 ******************************************************************************
 */
 
#ifndef __ENEMY_H__ 
#define __ENEMY_H__

#include "sprite.h"

typedef struct {
    Sprite super;
    
    uint8_t health;
    uint16_t missileFrameTimerCount;
} Enemy;

/**
 ******************************************************************************
 * @brief   Initialize an Enemy object
 ******************************************************************************
 */
void Enemy_ctor(Enemy * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, uint8_t health);

/**
 ******************************************************************************
 * @brief   Count down the frame timer.  Fires a missile when the timer runs
 *          out and resets the timer with a bounded random value.
 ******************************************************************************
 */
void Enemy_update(Enemy * const me);

/**
 ******************************************************************************
 * @brief   Enemy dies upon a colission with a PlayerMissile
 ******************************************************************************
 */
void Enemy_handleCollision(Enemy * const me, GameObject * const other);

#endif // __ENEMY_H__