#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_circle.h"
#include "status.h"
#include "engine.h"
#include <string.h>
 
typedef struct Player {
	CP_Vector pos;
	CP_Vector velocity;
	float speed;
	struct Health hp;
	struct Collider_Circle collider;
	struct Engine engine;
	struct Status status;
	int active;
	char name[10];
	int score;
	float bullet_diameter;
} Player;


struct Player Asteroids_Player_Init(float player_width, float player_height);
void Asteroids_Player_Update(Player* player);

void Asteroids_Player_Draw(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);

void Asteroids_Player_Calculate_Fuel(Player* player);
void Asteroids_Player_Drain_Fuel(Player* player);
void Asteroids_Player_Refuel(float amount, Player* player);

void Asteroids_Player_Debug(Player player);

void Asteroids_Player_Update_Movement(Player* player, float dt);
void Asteroids_Player_Simple_Movement(Player* player);
void Asteroids_Player_Check_Input(Player* player, float dt, CP_Vector direction);

void Asteroids_Player_Accelerate(Player* player, float dt, CP_Vector direction);
void Asteroids_Player_Decelerate(Player* player, float dt);
void Asteroids_Player_Strafe_Port(Player* player, float dt, CP_Vector direction);
void Asteroids_Player_Strafe_Starboard(Player* player, float dt, CP_Vector direction);

void Asteroids_Player_Death(Player* player);
void Asteroids_Player_Hit(Player* player);