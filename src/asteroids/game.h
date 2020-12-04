//---------------------------------------------------------
// file:	game.h
// author:	Lee Jia Keat
// contributors: Bryan Koh Yan Wei, Dania Mohd, Liu Ke
//
// brief:	Game scene header file.
//			Main scene of Asteroids.
//			Facilitates the gameplay of Asteroids.
//			Contains code for Initialization, Updating, Checking Input and Debugging the main game.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h" //CProcessing Framework, used to Render sprites and perform game logic (e.g. Vectors)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

#define ASTEROIDS_POOLSIZE_BULLETS 19999
#define ASTEROIDS_POOLSIZE_ENEMIES 650
#define ASTEROIDS_ENEMY_SPRITE_COUNT 5

typedef int DIFFICULTY;
enum DIFFICULTY_TYPE {EASY = 1, NORMAL, HARD, INSANE, IMPOSSIBLE, PEPEGA, BRUH};

extern DIFFICULTY ASTEROIDS_GAME_DIFFICULTY;
extern DIFFICULTY DIFFICULTY_OPTION;

void Asteroids_Init(void);
void Asteroids_Update(void);
void Asteroids_Exit(void);
void Asteroids_Cleanup(void);

void Asteroids_Check_Input();

void Asteroids_Draw();
void Asteroids_FPS_Draw();

void Asteroids_Debug();
void Asteroids_Debug_Check_Input();

void Asteroids_Sprites_Load();
void Asteroids_Entities_Init();

void Asteroids_Player_Rotate(CP_Vector direction);

void Asteroids_Cooldown_Update();

//Difficulty
void Asteroids_Set_Difficulty(DIFFICULTY difficulty);
void Asteroids_Difficulty_Update();
void Asteroids_Raise_Difficulty();