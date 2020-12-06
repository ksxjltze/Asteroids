#pragma once
//---------------------------------------------------------
// file:	bigboy.c
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//
// brief:	Spawns a super asteroid enemy after every 60s.
//			Boss may spawn on any side of the screen.
//			Kills the player instantly upon contact.
//			Creates a shockwave which kills every asteroid on the field upon death.
//			Hp scales with difficulty as time progresses.
//			
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "enemy.h"
#include "utility.h"
#include "player.h"
#include "bullet.h"

/*				SUPER ASTEROID MAIN ENTRY FUNCTIONS		*/
void Asteroids_Boss_Init(CP_Image EnemySprite[], CP_Image EnemyHurtSprite[], float enemy_width, float enemy_height, Player* player);
void Asteroids_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[]);



/*				SUPER ASTEROID DRAWING FUNCTION			*/
void Asteroids_Enemy_Draw_Boss(void);



/*				SUPER ASTEROID SPAWNING MANAGER			*/
void Asteroids_Enemy_Boss_Spawn(void);



/*				SUPER ASTEROID HELPER FUNCTIONS			*/
void Asteroids_Enemy_Check_Boss_Hp(Enemy* boss, Player player, Enemy enemy_pool[], int count);
void Asteroids_Enemy_Boss_Spawn_Interval(void);
CP_Vector Asteroids_Boss_Random_Spawn_Location(void);
CP_Vector Asteroids_Boss_Get_Position(void);



/*				SUPER ASTEROID COLLISION FUNCTION		*/
Bullet Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(Enemy* boss, Bullet bullet, Player* player);



/*				SUPER ASTEROID VFX FUNCTION				*/
void Asteroids_Enemy_Boss_Death_Circle(Enemy* boss, Player player, Enemy enemy_pool[], int count);