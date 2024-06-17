#include "sprite.h"
#include "game_engine.h"
#include "Nokia5110.h"

void Sprite_ctor(Sprite * const me, unsigned char const * bmp, uint8_t x_pos, uint8_t y_pos, bool bounded) {
    static const struct GameObjectVtable vtable = {
        .update = (void (*)(GameObject * const me))&Sprite_update,
        .getBmp = (unsigned char const * (*)(GameObject const * const me))&Sprite_getBmp,
        .getX = (uint8_t (*)(GameObject const * const me))&Sprite_getX,
        .getY = (uint8_t (*)(GameObject const * const me))&Sprite_getY,
        .checkCollision = (bool (*)(GameObject const * const me, GameObject const * const other))&Sprite_checkCollision,
        .handleCollision = (void (*)(GameObject * const me, GameObject * const other))&GameObject_handleCollision
    };
    
    GameObject_ctor(&me->super);
    me->super.vptr = &vtable;
    
    me->bmp = bmp;
    me->x_pos = x_pos;
    me->y_pos = y_pos;
    me->bounded = bounded;
    me->height = bmp[22];
    me->width = bmp[18];
    me->super.objectType = Undefined;
}


void Sprite_update(Sprite * const me) {
    (void)me;
}

bool Sprite_checkCollision(Sprite const * const me, GameObject const * const other) {

    
    // other object must be a sprite for collision to be possible
    if (other->objectType == Undefined) {
        return false;
    }
    
    Sprite const * const otherSprite = (Sprite*)other;
    
        // DEBUG
    if (me->super.objectType == PlayerMissileType) {
        
    }
    if (me->super.objectType == PlayerMissileType && otherSprite->super.objectType == EnemyType) {
        // breakpoint
    }
    if (me->super.objectType == EnemyType && otherSprite->super.objectType == PlayerMissileType) {
        // breakpoint
    }
    
    // get bounds of each sprite
    long widthMe = me->bmp[18];
    long heightMe = me->bmp[22];
    uint8_t bottomLeftMeX = me->x_pos;
    uint8_t bottomLeftMeY = me->y_pos;
    uint8_t topRightMeX = me->x_pos + widthMe-1;
    uint8_t topRightMeY = me->y_pos + heightMe-1;
    
    long widthOther = otherSprite->bmp[18];
    long heightOther = me->bmp[22];
    uint8_t bottomLeftOtherX = otherSprite->x_pos;
    uint8_t bottomLeftOtherY = otherSprite->y_pos;
    uint8_t topRightOtherX = otherSprite->x_pos + widthOther-1;
    uint8_t topRightOtherY = otherSprite->y_pos + heightOther-1;
    
   // bool horizontalOverlap = false, verticalOverlap = false;
    
    // check horizontal overlap
    /*
    if ((bottomLeftMeX < bottomLeftOtherX && topRightMeX > bottomLeftOtherX)
        || (bottomLeftMeX < topRightOtherX && topRightMeX > topRightOtherX)) {
        horizontalOverlap = true;
    }
    */
    
    if (topRightMeX < bottomLeftOtherX || bottomLeftMeX > topRightOtherX) {
        return false;
    }
    if (bottomLeftMeY > topRightOtherY || topRightMeY < bottomLeftOtherY) {
        return false;
    }
    return true;
   
    
    // check vertical overlap
    /*
    if ((bottomLeftMeY < bottomLeftOtherY && topRightMeY > bottomLeftOtherY) 
        || (bottomLeftMeY < topRightOtherY && topRightMeY > topRightOtherY)) {
        verticalOverlap = true;
    }
    */
        

    /*
    // There is a collision iff there is both horizontal and vertical overlap
    if (verticalOverlap && horizontalOverlap) {
        return true;
    }
    else {
        return false;
    }
    */
}

unsigned char const * Sprite_getBmp(Sprite const * const me) {
    return me->bmp;
}
uint8_t Sprite_getX(Sprite const * const me) {
    return me->x_pos;
}
uint8_t Sprite_getY(Sprite const * const me) {
    return me->y_pos;
}


void Sprite_moveBy(Sprite * const me, int16_t dx, int8_t dy) {
    
    long width = me->bmp[18], height = me->bmp[22];

    int16_t new_x_pos = me->x_pos + dx;
    int16_t new_y_pos = me->y_pos + dy;
 
    // bound the x and y position results to the screen dimensions
    if (me->bounded) {
        if (new_x_pos + width > SCREEN_WIDTH-1) {
            new_x_pos = SCREEN_WIDTH-width-1;
        } 
        else if (new_x_pos < 0) {
            new_x_pos = 0;
        } // bottom
        if (new_y_pos > SCREEN_HEIGHT-1) {
            new_y_pos = SCREEN_HEIGHT-1;
        } // top
        else if (new_y_pos - height < 0) {
            new_y_pos = height;
        }   
    } 
    else {
        // TODO (maybe) if unbounded, the sprite should cut partially cut off
        // if unbounded, the sprite should destroy itself if it is going to be cutoff
        if (((new_x_pos + width) > SCREENW) || // right side cut off
             (new_y_pos < (height - 1)) ||      // top cut off
             (new_y_pos > SCREENH)) // bottom cut off
        { 
            GameObject_kill((GameObject*)me);
        }
    }
    
    me->x_pos = (uint8_t)new_x_pos;
    me->y_pos = (uint8_t)new_y_pos;
}

bool Sprite_isOnScreen(Sprite const * const me) { 
    if (me->x_pos < 0 || me->x_pos + me->width > SCREEN_WIDTH
        || me->y_pos - me->height+1 < 0 || me->y_pos > SCREEN_HEIGHT) {
            return false;
        }
    else {
        return true;
    }
}