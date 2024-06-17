/**
 ******************************************************************************
 * @file    enemy.c
 * @author  Patrick Smith
 * @brief   Code for an Enemy object which inherits from Sprite
 ******************************************************************************
 * Contains the intializer function, update and handleCollision virtual 
 * functions for the Enemy object.
 ******************************************************************************
 */
#include "enemy.h"
#include "game_engine.h"
#include <stdlib.h>

#define MISSILE_RELOAD_UPPER_BOUND 7000
#define MISSILE_RELOAD_LOWER_BOUND 3000
#define MS_PER_SECOND 1000

/**
 ******************************************************************************
 * @brief   Initialize an Enemy object
 ******************************************************************************
 */
void Enemy_ctor(Enemy * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, uint8_t health) {
    static const struct GameObjectVtable vtable = {
        .update = (void (*)(GameObject * const me))&Enemy_update,
        .getBmp = (unsigned char const * (*)(GameObject const * const me))&Sprite_getBmp,
        .getX = (uint8_t (*)(GameObject const * const me))&Sprite_getX,
        .getY = (uint8_t (*)(GameObject const * const me))&Sprite_getY,
        .checkCollision = (bool (*)(GameObject const * const me, GameObject const * const other))&Sprite_checkCollision,
        .handleCollision = (void (*)(GameObject * const me, GameObject * const other))&Enemy_handleCollision        
    };
    
    Sprite_ctor(&me->super, bmp, x_pos, y_pos, true);
    ((GameObject*)me)->vptr = &vtable;
    ((GameObject*)me)->objectType = EnemyType;
    
    me->health = health;
    // start countdown until firing a missile
    uint16_t ms = rand() % (MISSILE_RELOAD_UPPER_BOUND - MISSILE_RELOAD_LOWER_BOUND + 1) + MISSILE_RELOAD_LOWER_BOUND;
    me->missileFrameTimerCount = ms * SYSTICK_FREQ / MS_PER_SECOND;
}

/**
 ******************************************************************************
 * @brief   Count down the frame timer.  Fires a missile when the timer runs
 *          out and resets the timer with a bounded random value.
 ******************************************************************************
 */
void Enemy_update(Enemy * const me) {    
    --me->missileFrameTimerCount;
    
    // fire a missile and reset the counter
    if (me->missileFrameTimerCount == 0) {
        enemyFireMissile(me);
        
        uint16_t ms = rand() % (MISSILE_RELOAD_UPPER_BOUND - MISSILE_RELOAD_LOWER_BOUND + 1) + MISSILE_RELOAD_LOWER_BOUND;
        me->missileFrameTimerCount = ms * SYSTICK_FREQ / MS_PER_SECOND;
    } 
}

/**
 ******************************************************************************
 * @brief   Enemy dies upon a colission with a PlayerMissile
 ******************************************************************************
 */
void Enemy_handleCollision(Enemy * const me, GameObject * const other) {
    switch(other->objectType) {
        case PlayerMissileType:
            GameObject_kill((GameObject*)me);
        default: // ignore all other collisions
            break;
    }
}
