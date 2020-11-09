#pragma once
#include "cprocessing.h"
#include "enemy.h"

typedef struct Bullet {
	CP_Vector pos;
	struct Collider_Circle collider;
	CP_Vector velocity;
	int active;
} Bullet;

void Asteroids_Bullet_Init(Bullet arr_bullet[], int count, float bullet_width, float bullet_height);
void Asteroids_Bullet_Update(Bullet arr_bullet[], int bullet_count, Enemy arr_enemy[], int enemy_count);
void Asteroids_Bullet_Draw(Bullet arr_bullet[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height);
void Asteroids_Bullet_Debug(Bullet arr_bullet[], int count);
void Asteroids_Bullet_Spawn(Bullet bullets[], int count, Player player, CP_Vector shoot_direction);