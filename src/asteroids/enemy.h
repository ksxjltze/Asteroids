#pragma once
#include "cprocessing.h"
#include "player.h"
#include "game.h"

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
	int split_count;

	int id;
	int parent_id;

	int sprite_type;
} Enemy;

void Asteroids_Enemy_Init(Enemy enemy_pool[], int count, float enemy_width, float enemy_height, Player player);
void Asteroids_Enemy_Update(Enemy enemy_pool[], int count ,Player player);
void Asteroids_Enemy_Draw(Enemy enemy_pool[], int count, CP_Image sprites[], CP_Image hurt_sprites[], float enemy_width, float enemy_height);
void Asteroids_Enemy_Idle_Rotate(Enemy* enemy, float rotate_rate, float dt);

void Asteroids_Enemy_Collide(Enemy* enemy1, Enemy* enemy2, Enemy enemy_pool[], int enemy_count, Player player);
void Asteroids_Enemy_Death(Enemy* enemy);
void Asteroids_Enemy_Debug(Enemy enemy_pool[], int count);

void Asteroids_Enemy_Init_Spawn(Enemy enemy_pool[], int count, Player player);
void Asteroids_Enemy_Spawn_Static(Enemy enemy_pool[], int count, Player player);
void Asteroids_Enemy_Spawn(Enemy enemy_pool[], int count);
void Asteroids_Enemy_Spawn_Timer(Enemy enemy_pool[], int count);
void Asteroids_Enemy_Spawn_Set_Interval(float interval);
void Asteroids_Enemy_Spawn_Decrease_Interval(float amount);
void Asteroids_Enemy_Spawn_Scale_Interval(DIFFICULTY difficulty);

CP_Vector Asteroids_Enemy_Random_Pos();
CP_Vector Asteroids_Enemy_Random_Velocity(CP_Vector pos, float speed);
float Asteroids_Enemy_Random_Speed();
void Asteroids_Enemy_Reset(Enemy* enemy);
float Asteroids_Enemy_Random_Rotation();

void Asteroids_Enemy_Split(Enemy* enemy, Player player, Enemy enemy_pool[], int count);
void Asteroids_Enemy_Check_OutOfBounds(Enemy enemy_pool[], int pool_size);
void Asteroid_Enemy_Check_Status(Enemy* enemy);
void Asteroids_Enemy_Hit(Enemy* enemy, float damage);

//LIU KE
void Asteroids_Enemy_Spawn_Child(Enemy enemy_pool[], int pool_count, Enemy parent, int count);

