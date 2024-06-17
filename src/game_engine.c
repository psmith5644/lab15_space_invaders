/**
 ******************************************************************************
 * @file    game_engine.c
 * @author  Patrick Smith
 * @brief   
 ******************************************************************************
 *
 * 
 ******************************************************************************
 */

#include "game_engine.h"
#include "sprite.h"
#include "Nokia5110.h"
#include "object_list.h"
#include "player.h"
#include "adc.h"
#include "bsp.h"
#include "missile.h"
#include "bunker.h"
#include "images.h"
#include "enemy_wave.h"
#include <stdlib.h>
#include "systick.h"
#include "sound.h"

#define MAX_OBJECTS 32
#define PLAYER_SPRITE_HEIGHT 8
#define PLAYER_SPRITE_WIDTH 18
#define PLAYER_MISSILE_SPEED 15
#define ENEMY_MISSILE_SPEED 15
#define START_SCREEN_DURATION 500

// An array of pointers to Sprite structs of all Sprites currently in game
GameObjectList objects;
bool waitForSysTick = true;
Missile enemyMissiles[ENEMIES_PER_WAVE];
extern uint32_t ms_elapsed;

// TODO: make some of the variables static to make them more optimal?

void play(void) {
    displayStartScreen();
    srand(ms_elapsed);

    GameObjectList_ctor(&objects);

    Player player;
    Player_ctor(&player, PlayerShip0, SCREENW / 2 - PLAYERW / 2, SCREEN_HEIGHT, true, 3, 1);
    player.super.super.index = GameObjectList_add(&objects, (GameObject*)&player);
    
    Bunker bunker;
    Bunker_ctor(&bunker, Bunker0, SCREEN_WIDTH / 2 - BUNKERW / 2, SCREEN_HEIGHT - PLAYER_SPRITE_HEIGHT, BUNKER_HEALTH);
    ((GameObject*)&bunker)->index = GameObjectList_add(&objects, (GameObject*)&bunker);
    
    EnemyWave wave;
    EnemyWave_ctor(&wave, 1, 1, 15);
    wave.super.index = GameObjectList_add(&objects, (GameObject*)&wave);
    
    uint8_t button0PressedLastFrame = 0;
    uint8_t button1PressedLastFrame = 0;
    while(1) {
        // At 30 Hz (wait for semaphore)
        while(waitForSysTick);
        waitForSysTick = true;

        // check if user buttons have been pressed since last frame
        uint8_t button0Pressed = readButton0_RIS();
        uint8_t button1Pressed = readButton1_RIS();
        

        
        // FIXME: the playerMissile is always in the same spot in memory so after multiple shots there are now multiple missile
        // in the objects array
        // shouldn't be a problem because the bitmap will always ensure that any copies are not used.
        // FIXME: missile copies add up and some of them have the wrong index.  
        // TODO: test if this declaration can be file-scope
        Missile playerMissile;
        
        // update LEDs
        if (GameObject_isAlive((GameObject*)&playerMissile)) {
            green_LED_off();
            red_LED_on();
        }
        else {
            green_LED_on();
            red_LED_off();
        }
            
        
        uint8_t missileX = Sprite_getX((Sprite*)&player) + (PLAYER_SPRITE_WIDTH / 2);
        uint8_t missileY = Sprite_getY((Sprite*)&player) - PLAYER_SPRITE_HEIGHT;
        if (button0Pressed && !button0PressedLastFrame && !GameObject_isAlive((GameObject*)&playerMissile)) {
            // launch player missile
            Missile_ctor(&playerMissile, Missile0, missileX, missileY, PLAYER_MISSILE_SPEED, Up, PlayerTeam);
            ((GameObject*)&playerMissile)->index = GameObjectList_add(&objects, (GameObject*)&playerMissile);
            Sound_Shoot(); // TEST
        }
        if (button1Pressed) {
            // launch player bomb
        }

        
        // update each game object
        for (int i = 0; i < MAX_OBJECTS; i++) {
            if (objects.bitmap & (1 << i)) {
                GameObject_update_vcall(objects.objects[i]);
            }
            
        }
        
        // handle collisions between sprites
        for (int i = 0; i < MAX_OBJECTS; i++) {
            if (!(objects.bitmap & (1 << i))) {
                continue;
            }
            for (int j = i+1; j < MAX_OBJECTS; j++) {
                if (!(objects.bitmap & (1 << j))) {
                    continue;
                }
                if (GameObject_checkCollision_vcall(objects.objects[i], objects.objects[j])) {
                    GameObject_handleCollision_vcall(objects.objects[i], objects.objects[j]);
                    GameObject_handleCollision_vcall(objects.objects[j], objects.objects[i]);
                }

            }
        }
        
        
        
        // print to the screen
        Nokia5110_ClearBuffer();
        Nokia5110_Clear();
        for (int i = 0; i < MAX_OBJECTS; i++) {
            if (!(objects.bitmap & (1 << i))) {
                continue;
            }
            GameObject * obj = objects.objects[i];
            if (GameObject_isAlive(obj)) {
                Nokia5110_PrintBMP(GameObject_getX_vcall(obj), GameObject_getY_vcall(obj), GameObject_getBmp_vcall(obj), 0);
            }
        }
        Nokia5110_DisplayBuffer();
        
        // button debouncing by an extra frame (+33.3 ms)
        button0PressedLastFrame = button0Pressed;
        button1PressedLastFrame = button1Pressed;
        
        // TODO check for win
        bool win = true;
        for (uint8_t i = 0; i < ENEMIES_PER_WAVE; i++) {
            Enemy enemy = wave.enemies[i];
            if (((GameObject*)&enemy)->alive) {
                win = false;
            }
        }
        if (win) {
            displayWinScreen();
            return;
        }
        
        // TODO check for loss
        
    }
}

void destroyGameObject(GameObject * const obj) {
    GameObjectList_remove(&objects, obj->index);
}

// TEST
// FIXME: missiles get launched from weird spots
void enemyFireMissile(Enemy const * const enemy) {
    for (uint8_t i = 0; i < ENEMIES_PER_WAVE; i++) {
        if (!(GameObject_isAlive((GameObject*)&enemyMissiles[i])))
        {
            Missile_ctor(&enemyMissiles[i], Missile1, ((Sprite*)enemy)->x_pos + ENEMY10W/2, ((Sprite*)enemy)->y_pos + MISSILEH, ENEMY_MISSILE_SPEED, Down, EnemyTeam); 
            ((GameObject*)&enemyMissiles[i])->index = GameObjectList_add(&objects, (GameObject*)&enemyMissiles[i]);
            break;
        }
    }
}

void displayStartScreen() {
    char * const title = 
        "   Space    "
        "  Invaders  "
        "            "
        "    by      "
        "  Patrick   "
        "   Smith    ";
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_OutString(title);
    uint8_t counter = 0;
    while (counter < START_SCREEN_DURATION / 33) {
        if (!waitForSysTick) {
            ++counter;
        }
        waitForSysTick = true;
    }
    
    char * const pressToStart = 
        "            "
        "   Press    "
        "   Fire to  "
        "   Start    "
        "            "
        "            ";
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_OutString(pressToStart);
    while(!readButton0_RIS());
    while(waitForSysTick);
    waitForSysTick = true;
}

void displayWinScreen() {
    char * const winScreen = 
        "            "
        "            "
        "    You     "
        "    Win!    "
        "            "
        "            ";
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_OutString(winScreen);
}
void displayGameOverScreen() {
    char * const gameOverScreen = 
        "            "
        "            "
        "    Game    "
        "    Over    "
        "            "
        "            ";
    Nokia5110_Clear();
    Nokia5110_ClearBuffer();
    Nokia5110_OutString(gameOverScreen);
    
    while (1);
}

