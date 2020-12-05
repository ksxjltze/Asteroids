//---------------------------------------------------------
// file:	bullet.h
// author:	Lee Jia Keat
// contributors: Liu Ke (Initial code for Asteroid Splitting)
//				 Bryan (Bullet splitting implementation)
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Bullet entity header file.
//			Handles Initialization, Updating and Drawing
//			of a specified pool (static array) of bullet entities.
//			Provides an interface for spawning (firing) bullets.
//			Contains implementation of multishot (split bullets) powerup.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"
#include "enemy.h"

enum Bullet_Type { LINEAR_PROJECTILE, HOMING_PROJECTILE };
typedef struct Bullet {
	CP_Vector pos;
	CP_Vector velocity;
	CP_Vector target;
	struct Collider_Circle collider;
	float rotation;
	int active;
	int id;
	int type;
} Bullet;


void Asteroids_Bullet_Init(Bullet bullets[], int count, float bullet_width, float bullet_height);
void Asteroids_Bullet_Update(Bullet bullets[], int bullet_count, Enemy enemy_pool[], int enemy_count, Player player);
void Asteroids_Bullet_Draw(Bullet bullets[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height);
void Asteroids_Bullet_Debug(Bullet bullets[], int count);
Bullet* Asteroids_Bullet_Spawn(Bullet bullets[], int count, Player player, CP_Vector shoot_direction);
void Asteroids_Bullet_Powerup_Split(Bullet bullets[], int count, Player player, CP_Vector shoot_direction);
void Asteroids_Bullet_Split(Bullet bullets[], int pool_size, int bullet_count, float angle, Player player, CP_Vector shoot_direction);
Bullet* Asteroids_Bullet_Spawn_Homing(Bullet bullets[], int count, Player player, CP_Vector target, CP_Vector direction);
