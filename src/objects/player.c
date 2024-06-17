#include "player.h"
#include "adc.h"
#include "game_engine.h"

#define PLAYER_SHIP_WIDTH_PX 18
#define INVINCIBILITY_DURATION_MS 3000


static int16_t convert_to_pos(uint16_t voltage);
static void takeDamage(Player * const me, uint8_t const amt);
static void decrementInvincibility(Player * const me);
static float const position_coef = (float)(SCREEN_WIDTH - PLAYER_SHIP_WIDTH_PX) / (float)ADC_MAX_VAL;

void Player_ctor(Player * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, 
                 bool bounded, uint8_t health, uint8_t bombAmmo) {
    static const struct GameObjectVtable vtable = {
        .update = (void (*)(GameObject * const me))&Player_update,
        .getBmp = (unsigned char const * (*)(GameObject const * const me))&Sprite_getBmp,
        .getX = (uint8_t (*)(GameObject const * const me))&Sprite_getX,
        .getY = (uint8_t (*)(GameObject const * const me))&Sprite_getY,
        .checkCollision = (bool (*)(GameObject const * const me, GameObject const * const other))&Sprite_checkCollision,
        .handleCollision = (void (*)(GameObject * const me, GameObject * const other))&Player_handleCollision
    };
    Sprite_ctor(&me->super, bmp, x_pos, y_pos, bounded);
    me->super.super.vptr = &vtable;
    
    me->health = health;
    me->bombAmmo = bombAmmo;    
    me->super.super.objectType = PlayerType;
}

void Player_update(Player * const me) {
    uint16_t potentiometerSample = ADC1_sample();
    // TODO convert_to_pos could account for the 2 pixel buffer on each side of the playership to make the
    // controls more fine-tuned (there is small a dead zone at each end of the potentiometer)
    uint8_t desiredX = convert_to_pos(potentiometerSample); // TODO check assembly for this func
    Sprite_moveBy(&me->super, desiredX-me->super.x_pos, 0);
    decrementInvincibility(me);
}

uint8_t Player_addBombs(Player * const me, uint8_t quantity) {
    me->bombAmmo += quantity;
    return me->bombAmmo;
}

void Player_handleCollision(Player * const me, GameObject * const other) {
    // if invincible, ignore all collisions
    if (me->msInvincible > 0) {
        return;
    }
    
    // for both valid cases, take 1 damage
    switch(other->objectType) {
        case EnemyType:
            takeDamage(me, 1);
        case EnemyMissileType:
            takeDamage(me, 1);
        default: // ignore all other collisions
            break;
    }
}

static void takeDamage(Player * const me , uint8_t const amt) {
    me->health -= amt;
    if (me->health <= 0) {
        displayGameOverScreen();
    }
    // give invincibility 
    me->msInvincible = INVINCIBILITY_DURATION_MS;
}

static void decrementInvincibility(Player * const me) {
    if (me->msInvincible > 0) {
        me->msInvincible -= 1000/SYSTICK_FREQ;
    }
    if (me->msInvincible < 0) {
        me->msInvincible = 0;
    }
}

/**
 ******************************************************************************
 * @brief   Converts ADC voltage to the desired position of the player's ship
 * @param   voltage: 12-bit voltage from potentiometer
 * @return  integer representing the desired x position of the player's ship
 ******************************************************************************
 */
static int16_t convert_to_pos(uint16_t voltage) {
    return (uint8_t)(voltage * position_coef); // [0:MAX_ADC_VAL] -> [0:SCREEN_WIDTH - PLAYER_SHIP_WIDTH]
}