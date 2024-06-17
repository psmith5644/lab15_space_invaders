#include "game_object.h"
#include "game_engine.h"
#include "object_list.h"

extern GameObjectList objects;

void GameObject_ctor(GameObject * const me) {
    static const struct GameObjectVtable vtable = {
        .update = &GameObject_update,
        .getBmp = &GameObject_getBmp,
        .getX = &GameObject_getX,
        .getY = &GameObject_getY,
        .checkCollision = &GameObject_checkCollision,
        .handleCollision = &GameObject_handleCollision
    };
    me->vptr = &vtable;
    
    me->alive = true;
    me->objectType = Undefined;
}

void GameObject_update(GameObject * const me) {
    (void)me;
}

unsigned char const * GameObject_getBmp(GameObject const * const me) {
    (void)me;
    return 0;
}
uint8_t GameObject_getX(GameObject const * const me) {
    (void)me;
    return 0;
}
uint8_t GameObject_getY(GameObject const * const me) {
    (void)me;
    return 0;
}

bool GameObject_checkCollision(GameObject const * const me, GameObject const * const other) {
    (void)me;
    (void)other;
    return false;
}

void GameObject_handleCollision(GameObject * const me, GameObject * const other) {
    (void)me;
    (void)other;
}

bool GameObject_isAlive(GameObject const * const me) {
    return me->alive;
}

void GameObject_kill(GameObject * const me) {
    me->alive = false;
    destroyGameObject(me);
}

uint8_t GameObject_getIndex(GameObject const * const me) {
    return me->index;
}

GameObjectType GameObject_getObjectType(GameObject const * const me) {
    return me->objectType;
}

