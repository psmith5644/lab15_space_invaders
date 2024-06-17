/**
 ******************************************************************************
 * @file    enemy_wave.c
 * @author  Patrick Smith
 * @brief   Code for the EnemyWave GameObject, which controls a group of Enemies
 ******************************************************************************
 * The EnemyWave GameObject contains a list of enemies and handles the 
 * movement of all enemies in the wave
 ******************************************************************************
 */
 
#include "enemy_wave.h"
#include "images.h"
#include "object_list.h"
#include "Nokia5110.h"
#include <stdlib.h>


#define WAVE_DOWN_DISTANCE 4
#define WAVE_STARTING_X 0
#define WAVE_STARTING_Y 0

extern GameObjectList objects;

static void getWaveDimensions(EnemyWave * const me, uint8_t * leftmostEdge, uint8_t * rightmostEdge, uint8_t * bottommostEdge);
static void moveWave(EnemyWave * const me, Direction const direction);

/**
 ******************************************************************************
 * @brief   Initialize an EnemyWave object and all Enemies in the wave
 ******************************************************************************
 */
void EnemyWave_ctor(EnemyWave * const me, uint8_t speed, uint8_t fireRate, uint8_t missileSpeed) {
    static const struct GameObjectVtable vtable = {
        .update = (void (*)(GameObject * const me))&EnemyWave_update,
        .getBmp = &GameObject_getBmp,
        .getX = &GameObject_getX,
        .getY = &GameObject_getY,
        .checkCollision = &GameObject_checkCollision,
        .handleCollision = &GameObject_handleCollision
    };
    
    GameObject_ctor(&me->super);
    ((GameObject*)me)->vptr = &vtable;
    
    me->speed = speed;
    me->fireRate = fireRate;
    me->missileSpeed = missileSpeed;
    me->moveDownDistanceCounter = 0;
    me->movementFrameCounter = 0;
    me->movementFrameNum = SYSTICK_FREQ/speed;
    me->currDirection = Left;
    
    // initialize all enemies in this wave
    for (uint8_t i = 0; i < ENEMIES_PER_WAVE; i++) {
        Enemy_ctor(&me->enemies[i], SmallEnemy10PointA, i*ENEMY10W, ENEMY10H, 1);
        ((GameObject*)&me->enemies[i])->index = GameObjectList_add(&objects, (GameObject*)&me->enemies[i]);
    }
}

// BUG: sometimes enemy wave gets stuck moving straight down if there is only one alien left
// probably caused by constantly alternating the direction between Left and Right because the last enenmy is both the leftmost and rightmost enemy
/**
 ******************************************************************************
 * @brief   Updates the position of all Enemies in the wave
 ******************************************************************************
 */
void EnemyWave_update(EnemyWave * const me) {
    // check position of leftmost and rightmost alive enemies in the wave
    // this info is used to determine when the wave hits an edge of the screen
    uint8_t leftmostEdge, rightmostEdge, bottommostEdge;
    getWaveDimensions(me, &leftmostEdge, &rightmostEdge, &bottommostEdge);
    
    if (bottommostEdge >= SCREENH) {
        displayGameOverScreen();
    }
    
    // if one of their position + direction is about to hit a wall, change the direction to down
    switch(me->currDirection) {
        case Left:
            if (leftmostEdge - 1 < SCREEN_LEFT_EDGE) {
                me->prevDirection = me->currDirection;
                me->currDirection = Down;
            }
            break;
        case Right:
            if (rightmostEdge + 1 > SCREEN_RIGHT_EDGE) {
                me->prevDirection = me->currDirection;
                me->currDirection = Down;
            }
            break;
        // if the direction is down, keep moving until the down distance has been met
        // then switch to the opposite direction
        case Down:
            if (me->moveDownDistanceCounter >= WAVE_DOWN_DISTANCE) {
                if (me->prevDirection == Left) {
                    me->currDirection = Right;
                    me->prevDirection = Down;
                }
                else if (me->prevDirection == Right) {
                    me->currDirection = Left;
                    me->prevDirection = Down;
                }
                me->moveDownDistanceCounter = 0;
            }
            break;
        default:
            break;
    }
    // move wave based on current direction and speed 
    ++me->movementFrameCounter;
    if (me->movementFrameCounter >= me->movementFrameNum) {
        switch(me->currDirection) {
            case Left:
                moveWave(me, Left);
                break;
            case Right:
                moveWave(me, Right);
                break;
            case Down:
                moveWave(me, Down);
                ++me->moveDownDistanceCounter;
                break;
            default:
                break;
        }
        me->movementFrameCounter = 0;
    }
}


/**
 ******************************************************************************
 * @brief   Gets the positions of the enemies that are closest to the screen edges
 * @param   takes three integer pointers that will be modified by this function
 ******************************************************************************
 */
static void getWaveDimensions(EnemyWave * const me, uint8_t * leftmostEdge, uint8_t * rightmostEdge, uint8_t * bottommostEdge) {
    uint8_t leftmostPos = SCREEN_WIDTH, rightmostPos = 0, bottommostPos = 0;
    for (uint8_t i = 0; i < ENEMIES_PER_WAVE; i++) {
        Enemy * enemy = &me->enemies[i];
        rightmostPos = MAX(rightmostPos, ((Sprite*)enemy)->x_pos);
        leftmostPos = MIN(leftmostPos, ((Sprite*)enemy)->x_pos);
        bottommostPos = MAX(bottommostPos, ((Sprite*)enemy)->y_pos);
    }
    *leftmostEdge = leftmostPos;
    *rightmostEdge = rightmostPos + ENEMY10W;
    *bottommostEdge = bottommostPos;
}


/**
 ******************************************************************************
 * @brief   Iterates over all enemies and moves them one pixel in the 
 *          corresponding @direction
 ******************************************************************************
 */
static void moveWave(EnemyWave * const me, Direction const direction) {
    for (uint8_t i = 0; i < ENEMIES_PER_WAVE; i++) {
        Enemy * enemy = &me->enemies[i];
        if (!((GameObject*)enemy)->alive) {
            continue;
        }
        
        switch(direction) {
            case Left:
                ((Sprite*)enemy)->x_pos -= 1;
                break;
            case Right:
                ((Sprite*)enemy)->x_pos += 1;
                break;
            case Down:
                ((Sprite*)enemy)->y_pos += 1;
                break;
            default:
                break;
        }
    }
}