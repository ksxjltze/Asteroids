#pragma once
#include "cprocessing.h"
#include "enemy.h"

typedef struct Bullet {
	CP_Vector pos;
	struct Collider_Circle collider;
	CP_Vector velocity;
	float rotation;
	int active;
} Bullet;

void Asteroids_Bullet_Init(Bullet bullets[], int count, float bullet_width, float bullet_height);
void Asteroids_Bullet_Update(Bullet bullets[], int bullet_count, Enemy enemy_pool[], int enemy_count);
void Asteroids_Bullet_Draw(Bullet bullets[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height);
void Asteroids_Bullet_Debug(Bullet bullets[], int count);
void Asteroids_Bullet_Spawn(Bullet bullets[], int count, Player player, CP_Vector shoot_direction);
void Asteroids_Bullet_Powerup_Split(Bullet bullets[], int count, Player player, CP_Vector shoot_direction);