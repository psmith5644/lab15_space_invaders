#include "missile.h"
#include "game_engine.h"
#include "bunker.h"
#include "sound.h"

static void Missile_explode(Missile * const me);

void Missile_ctor(Missile * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, 
                  uint8_t speed, Direction direction, Team team) {
    static const struct GameObjectVtable vtable = {
        .update = (void (*) (GameObject * const me))&Missile_update,
        .getBmp = (unsigned char const * (*)(GameObject const * const me))&Sprite_getBmp,
        .getX = (uint8_t (*)(GameObject const * const me))&Sprite_getX,
        .getY = (uint8_t (*)(GameObject const * const me))&Sprite_getY,
        .checkCollision = (bool (*)(GameObject const * const me, GameObject const * const other))&Sprite_checkCollision,
        .handleCollision = (void (*)(GameObject * const me, GameObject * const other))&Missile_handleCollision
    };
    
    Sprite_ctor(&me->super, bmp, x_pos, y_pos, false);
    me->super.super.vptr = &vtable;
    
    me->speed = speed; // pixels/second Range=[1:SYSTICK_FREQ]
    me->direction = direction;
    me->team = team;
    if (team == PlayerTeam) {
        me->super.super.objectType = PlayerMissileType;
    }
    else {
        me->super.super.objectType = EnemyMissileType;
    }
    me->frameCount = 0;
    me->positionUpdateFrame = SYSTICK_FREQ/speed;
}
                  
// TODO implement speed param 
void Missile_update(Missile * const me) {
    bool isOnScreen = Sprite_isOnScreen((Sprite*)me);
    if (!isOnScreen) {
        GameObject_kill((GameObject*)me);
        return;
    }
    
    me->frameCount++;
    if (me->frameCount < me->positionUpdateFrame) {
        return;
    }
    else {
        me->frameCount = 0;
    }
        
    if (me->direction == Up) {
        Sprite_moveBy(&me->super, 0, -1); 
    }
    else if (me->direction == Down) {
        Sprite_moveBy(&me->super, 0, 1);
    }
}

void Missile_handleCollision(Missile * const me, GameObject * const other) {
    switch(other->objectType) {
        case PlayerType:
            if (me->team == EnemyTeam) {
                Missile_explode(me);
            }
            break;
        case EnemyType:
            if (me->team == PlayerTeam) {
                Missile_explode(me);
            }
            break;
        case BunkerType: { 
            Bunker * bunker = (Bunker*)other;
            if (bunker->health > 0) {
                Missile_explode(me);
            }
            break;
        }
        default:
            break;
    }
}

// TODO implement
static void Missile_explode(Missile * const me) {
    // switch texture, stop, wait, then kill later
    Sound_Explosion();
    GameObject_kill((GameObject*)me);
}