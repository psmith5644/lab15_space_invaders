/**
 ******************************************************************************
 * @file    game_engine.h
 * @author  Patrick Smith
 * @brief   
 ******************************************************************************
 *
 * 
 ******************************************************************************
 */
 
#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#include <stdint.h>
#include "game_object.h"
#include "enemy.h"


#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48
#define SCREEN_LEFT_EDGE 0
#define SCREEN_RIGHT_EDGE 83
#define SCREEN_BOTTOM_EDGE 47
#define SCREEN_TOP_EDGE 0

#define SYSTICK_FREQ 30
#define BUNKER_HEALTH 10
#define ENEMIES_PER_WAVE 5
#define TIMER2A_FREQ 11025

    
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))



/**
 ******************************************************************************
 * @brief   Draws all sprites onto the screen.
 ******************************************************************************
 */
void draw(void);

void play(void);

void destroyGameObject(GameObject * const obj);

void displayStartScreen();
void displayWinScreen();
void displayGameOverScreen();
void enemyFireMissile(Enemy const * const enemy);





#endif // __GAME_ENGINE_H__