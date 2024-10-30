#include "object_list.h"

/**
 ******************************************************************************
 * @brief GameObjectList ctor, initializes bitmap that tracks used indices
 ******************************************************************************
 */
void GameObjectList_ctor(GameObjectList * const me) {
    me->bitmap = 0U;
}

/**
 ******************************************************************************
 * @brief Adds a game object to the list of all game objects, used by the game 
 *        engine.  Sets the object's index attribute.
 * @param obj game object to add to the list
 * @return error code
 ******************************************************************************
 */
ERR_t GameObjectList_Add(GameObjectList * const me, GameObject * const obj) {
    uint8_t index = 0;
    while (index < MAX_OBJECTS) {
        if ((me->bitmap & (1 << index)) == 0) {
            me->objects[index] = obj;
            me->bitmap |= (1 << index);
            obj->index = index;
            return SUCCESS; 
        }
        index++;
    }
    return ERR_OBJECTLIST_FULL;
}

/**
 ******************************************************************************
 * @brief Removes object at provided @index from object list
 * @param index of object to remove
 ******************************************************************************
 */
void GameObjectList_Remove(GameObjectList * const me, uint8_t index) {
    me->bitmap &= ~(1 << index);
}

/**
 ******************************************************************************
 * @brief checks if game object list is full
 * @return true of the object list is full, false otherwise
 ******************************************************************************
 */
bool GameObjectList_isFull(GameObjectList const * const me) {
    return (~me->bitmap == 0);
}