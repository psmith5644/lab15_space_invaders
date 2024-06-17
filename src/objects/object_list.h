#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include "game_object.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX_OBJECTS 32

typedef struct {
    GameObject * objects[MAX_OBJECTS];
    uint32_t bitmap;
} GameObjectList;

void GameObjectList_ctor(GameObjectList * const me);
uint8_t GameObjectList_add(GameObjectList * const me, GameObject * const obj);
void GameObjectList_remove(GameObjectList * const me, uint8_t index);
bool GameObjectList_isFull(GameObjectList const * const me);

#endif // __OBJECT_LIST_H__