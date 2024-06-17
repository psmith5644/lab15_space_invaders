#include "object_list.h"

void GameObjectList_ctor(GameObjectList * const me) {
    me->bitmap = 0U;
}

uint8_t GameObjectList_add(GameObjectList * const me, GameObject * const obj) {
    uint8_t index = 0;
    while (index < MAX_OBJECTS) {
        if ((me->bitmap & (1 << index)) == 0) {
            me->objects[index] = obj;
            me->bitmap |= (1 << index);
            return index;
        }
        index++;
    }
    return -1; // TODO assert failed: caller must check is_Full() before add()
}
void GameObjectList_remove(GameObjectList * const me, uint8_t index) {
    me->bitmap &= ~(1 << index);
}

bool GameObjectList_isFull(GameObjectList const * const me) {
    return (~me->bitmap == 0);
}