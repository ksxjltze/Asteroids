#pragma once
#include "cprocessing.h"
#include "enemy.h"
#include "utility.h"
#include "player.h"
#include "bullet.h"

void Asteroids_Final_Boss_Init(void);
void Asteroids_Final_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[]);
void Asteroids_Enemy_Final_Boss_Spawn(void);
