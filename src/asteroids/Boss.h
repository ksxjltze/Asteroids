#pragma once
#include "enemy.h"
#include "utility.h"
#include "player.h"
#include "bullet.h"



void Asteroids_Boss_Init(CP_Image EnemySprite[], CP_Image EnemyHurtSprite[], float enemy_width, float enemy_height, Player* player);

void Asteroids_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[]);

void Asteroids_Enemy_Draw_Boss(void);
void Asteroids_Enemy_Boss_Spawn(void);

CP_Vector Asteroids_Boss_Random_Spawn_Location(void);
Bullet Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(Enemy enemy_pool, Bullet bullet);