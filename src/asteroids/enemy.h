#pragma once
#include "cprocessing.h"
#include "player.h"

typedef struct Enemies {
	CP_Vector pos;
	CP_Vector velocity;
	float speed;
	struct Health hp;
	//struct Collider_AABB collider;

	struct Collider_Circle collider;
	int active;
	struct Status status;
} Enemy;

void Asteroids_Enemy_Init(Enemy arr_enemy[], int count, float enemy_width, float enemy_height, Player player);
void Asteroids_Enemy_Update(Enemy arr_enemy[], int count);
void Asteroids_Enemy_Draw(Enemy arr_enemy[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite, CP_Image health_bar_sprite);

void Asteroids_Enemy_Debug(Enemy arr_enemy[], int count);

void Asteroids_Enemy_Init_Spawn(Enemy arr_enemy[], int count, Player player);
void Asteroids_Enemy_Spawn_Static(Enemy arr_enemy[], int count, Player player);
void Asteroids_Enemy_Spawn(Enemy arr_enemy[], int count);
void Asteroids_Enemy_Spawn_Timer(Enemy arr_enemy[], int count);

CP_Vector Asteroids_Enemy_Random_Pos();
CP_Vector Asteroids_Enemy_Random_Velocity(CP_Vector pos, float speed);
float Asteroids_Enemy_Random_Speed();