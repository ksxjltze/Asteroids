#pragma once
#include "enemy.h"
#include "utility.h"


void Asteroids_Boss_Init(CP_Image EnemySprite[], CP_Image EnemyHurtSprite[], float enemy_width, float enemy_height);

void Asteroids_Boss_Update(void);

void Asteroids_Enemy_Draw_Boss(void);
void Asteroids_Enemy_Boss_Spawn(void);