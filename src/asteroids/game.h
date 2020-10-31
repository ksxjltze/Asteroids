#pragma once
#include "cprocessing.h" //CProcessing Framework, used to Render sprites and perform game logic (e.g. Vectors)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //Used to seed rand() function for random number generation.

#include "init.h"
#include "enemy.h"
#include "bullet.h"
#include "Heart.h"
#include "powerups.h"
#include "player.h"

#include "utility.h"
#include "gameover.h"
#include "pause.h"

void Asteroids_Init(void);
void Asteroids_Update(void);
void Asteroids_Exit(void);

void Asteroids_Check_Input();

void Asteroids_Draw();
void Asteroids_Debug();
void display_fps();

void Asteroids_Sprites_Load();
void Asteroids_Entities_Init();

void Asteroids_Player_Rotate(CP_Vector direction);

void Asteroids_Cooldown_Update();