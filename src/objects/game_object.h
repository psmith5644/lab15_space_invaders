#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <stdbool.h>
#include <stdint.h>


typedef enum {
    Undefined,
    PlayerType,
    EnemyType,
    EnemyMissileType,
    PlayerMissileType,
    BunkerType
} GameObjectType;

// TODO consider moving enums
typedef enum {
    Up,
    Down,
    Left,
    Right
} Direction;

typedef enum {
    PlayerTeam,
    EnemyTeam
} Team;

typedef struct {
    struct GameObjectVtable const *vptr; 
    bool alive;
    uint8_t index;
    GameObjectType objectType;
} GameObject;

struct GameObjectVtable {
    void (*update)(GameObject * const me);
    unsigned char const * (*getBmp)(GameObject const * const me);
    uint8_t (*getX)(GameObject const * const me);
    uint8_t (*getY)(GameObject const * const me);
    bool (*checkCollision)(GameObject const * const me, GameObject const * const other);
    void (*handleCollision)(GameObject * const me, GameObject * const other);
};

void GameObject_ctor(GameObject * const me);
bool GameObject_isAlive(GameObject const * const me);
void GameObject_kill(GameObject * const me);
uint8_t GameObject_getIndex(GameObject const * const me);
GameObjectType GameObject_getObjectType(GameObject const * const me);
void GameObject_handleCollision(GameObject * const me, GameObject * const other);
void GameObject_update(GameObject * const me);
unsigned char const * GameObject_getBmp(GameObject const * const me);
uint8_t GameObject_getX(GameObject const * const me);
uint8_t GameObject_getY(GameObject const * const me);
bool GameObject_checkCollision(GameObject const * const me, GameObject const * const other);

static inline void GameObject_update_vcall(GameObject * const me) {
    (*me->vptr->update)(me);
}

static inline unsigned char const * GameObject_getBmp_vcall(GameObject const * const me) {
    return (*me->vptr->getBmp)(me);
}

static inline uint8_t GameObject_getX_vcall(GameObject const * const me) {
    return (*me->vptr->getX)(me);
}

static inline uint8_t GameObject_getY_vcall(GameObject const * const me) {
    return (*me->vptr->getY)(me);
}

static inline void GameObject_handleCollision_vcall(GameObject * const me, GameObject * const other) {
    (*me->vptr->handleCollision)(me, other);
}

static inline bool GameObject_checkCollision_vcall(GameObject const * const me, GameObject const * const other) {
    return (*me->vptr->checkCollision)(me, other);
}





#endif // __GAME_OBJECT_H__