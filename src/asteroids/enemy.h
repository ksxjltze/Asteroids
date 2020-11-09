#pragma once
#include "cprocessing.h"
#include "player.h"

typedef struct Enemies {
	CP_Vector pos;
	CP_Vector velocity;
	float speed;
	float rotation;
	float rotate_rate;
	
	float size;
	struct Health hp;
	struct Collider_Circle collider;
	struct Status status;
	
	int active;
	int id;
	int parent_id;
} Enemy;

void Asteroids_Enemy_Init(Enemy enemy_pool[], int count, float enemy_width, float enemy_height, Player player);
void Asteroids_Enemy_Update(Enemy enemy_pool[], int count ,Player player);
void Asteroids_Enemy_Draw(Enemy enemy_pool[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite);
void Asteroids_Enemy_Idle_Rotate(Enemy* enemy, float rotate_rate, float dt);

void Asteroids_Enemy_Collide(Enemy* enemy1, Enemy* enemy2);
void Asteroids_Enemy_Death(Enemy* enemy);
void Asteroids_Enemy_Debug(Enemy enemy_pool[], int count);

void Asteroids_Enemy_Init_Spawn(Enemy enemy_pool[], int count, Player player);
void Asteroids_Enemy_Spawn_Static(Enemy enemy_pool[], int count, Player player);
void Asteroids_Enemy_Spawn(Enemy enemy_pool[], int count);
void Asteroids_Enemy_Spawn_Timer(Enemy enemy_pool[], int count);

//LIU KE
void Asteroids_Enemy_Spawn_Child(Enemy enemy_pool[], int count, Enemy parent);


CP_Vector Asteroids_Enemy_Random_Pos();
CP_Vector Asteroids_Enemy_Random_Velocity(CP_Vector pos, float speed);
float Asteroids_Enemy_Random_Speed();