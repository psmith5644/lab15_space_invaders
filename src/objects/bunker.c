/**
 ******************************************************************************
 * @file    bunker.c
 * @author  Patrick Smith
 * @brief   
 ******************************************************************************
 * 
 ******************************************************************************
 */
 
#include "bunker.h"
#include "game_engine.h"

extern const unsigned char Bunker3[];
extern const unsigned char Bunker2[];
extern const unsigned char Bunker1[];
extern const unsigned char Bunker0[];

static void takeDamage(Bunker * const me, uint8_t amt);

void Bunker_ctor(Bunker * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, uint8_t health) {
    static const struct GameObjectVtable vtable = {
        .update = (void (*)(GameObject * const me))&Bunker_update,
        .getBmp = (unsigned char const * (*)(GameObject const * const me))&Sprite_getBmp,
        .getX = (uint8_t (*)(GameObject const * const me))&Sprite_getX,
        .getY = (uint8_t (*)(GameObject const * const me))&Sprite_getY,
        .checkCollision = (bool (*)(GameObject const * const me, GameObject const * const other))&Sprite_checkCollision,
        .handleCollision = (void (*)(GameObject * const me, GameObject * const other))&Bunker_handleCollision
    };
    
    Sprite_ctor(&me->super, bmp, x_pos, y_pos, true);
    ((GameObject*)me)->vptr = &vtable;
    
    ((GameObject*)me)->objectType = BunkerType;
    me->health = health;
}

void Bunker_update(Bunker * const me) {
    
}
void Bunker_handleCollision(Bunker * const me, GameObject * const other) {
    switch(other->objectType) {
        case(EnemyMissileType):
            takeDamage(me, 1);
            break;
        case(PlayerMissileType):
            takeDamage(me, 1);
            break;
        default:
            break;
    }
}

static void takeDamage(Bunker * const me, uint8_t amt) {
    if (me->health > 0) {
        me->health--;       
    }
    if (me->health < BUNKER_HEALTH) {
        // moderately damaged texture
        ((Sprite*)me)->bmp = Bunker1;
    }
    if (me->health <= BUNKER_HEALTH / 2) {
        // severely damaged texture
        ((Sprite*)me)->bmp = Bunker2;
    }
    if (me->health <= 0) {
        GameObject_kill((GameObject*)me);
    }
}