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

#ifndef __ENEMY_WAVE_H__
#define __ENEMY_WAVE_H__

#include "game_object.h"
#include "enemy.h"
#include "game_engine.h"

typedef struct {
    GameObject super;
    
    Enemy enemies[ENEMIES_PER_WAVE];
    uint8_t speed;
    uint8_t fireRate;
    uint8_t missileSpeed;
    Direction currDirection;
    Direction prevDirection;
    uint8_t moveDownDistanceCounter; // counts the number of pixels the wave has moved down
    uint8_t movementFrameCounter; // counts the frames that have passed since the wave moved last
    uint8_t movementFrameNum; // the number of frames that must pass before the wave moves
} EnemyWave;

void EnemyWave_ctor(EnemyWave * const me, uint8_t speed, uint8_t fireRate, uint8_t missileSpeed);
void EnemyWave_update(EnemyWave * const me);

#endif // __ENEMY_WAVE_H__