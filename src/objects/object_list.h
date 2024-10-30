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

/**
 ******************************************************************************
 * @brief GameObjectList ctor, initializes bitmap that tracks used indices
 ******************************************************************************
 */
void GameObjectList_ctor(GameObjectList * const me);

/**
 ******************************************************************************
 * @brief Adds a game object to the list of all game objects, used by the game 
 *        engine.  Sets the object's index attribute.
 * @param obj game object to add to the list
 * @return error code
 ******************************************************************************
 */
ERR_t GameObjectList_Add(GameObjectList * const me, GameObject * const obj);

/**
 ******************************************************************************
 * @brief Removes object at provided @index from object list
 * @param index of object to remove
 ******************************************************************************
 */
void GameObjectList_Remove(GameObjectList * const me, uint8_t index);
/**
 ******************************************************************************
 * @brief checks if game object list is full
 * @return true of the object list is full, false otherwise
 ******************************************************************************
 */
bool GameObjectList_isFull(GameObjectList const * const me);

#endif // __OBJECT_LIST_H__