#pragma once
#include "cprocessing.h"
#include "player.h"

typedef struct Enemies {
	CP_Vector pos;
	CP_Vector velocity;
	float speed;
	float rotation;
	float rotate_rate;
	
	struct Health hp;
	struct Collider_Circle collider;
	struct Status status;
	
	int active;
} Enemy;

void Asteroids_Enemy_Init(Enemy enemy_pool[], int count, float enemy_width, float enemy_height, Player player);
void Asteroids_Enemy_Update(Enemy enemy_pool[], int count ,Player player);
void Asteroids_Enemy_Draw(Enemy enemy_pool[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite);
void Asteroids_Enemy_Idle_Rotate(Enemy* enemy, float rotate_rate, float dt);

void Asteroids_Enemy_Debug(Enemy enemy_pool[], int count);

void Asteroids_Enemy_Init_Spawn(Enemy enemy_pool[], int count, Player player);
void Asteroids_Enemy_Spawn_Static(Enemy enemy_pool[], int count, Player player);
void Asteroids_Enemy_Spawn(Enemy enemy_pool[], int count);
void Asteroids_Enemy_Spawn_Timer(Enemy enemy_pool[], int count);


void Asteroids_Enemysplit_Init(Enemy arr_enemysplit[], int count, float enemy_width, float enemy_height, Player player);
void Asteroids_Enemysplit_Update(Enemy arr_enemysplit[], int count);
void Asteroids_Enemysplit_Draw(Enemy arr_enemysplit[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite, CP_Image health_bar_sprite);
void Asteroids_Enemysplit_Init_Spawn(Enemy arr_enemysplit[], int count, Player player);
void Asteroids_Enemysplit_Spawn_Static(Enemy arr_enemysplit[], int count, Player player);
void Asteroids_Enemysplit_Spawn(Enemy arr_enemysplit[], int count);
void Asteroids_Enemysplit_Spawn_Timer(Enemy arr_enemysplit[], int count);


CP_Vector Asteroids_Enemy_Random_Pos();
CP_Vector Asteroids_Enemy_Random_Velocity(CP_Vector pos, float speed);
float Asteroids_Enemy_Random_Speed();