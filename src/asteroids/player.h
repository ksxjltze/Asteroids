#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_circle.h"
#include "status.h"
#include "engine.h"
#include <string.h>

typedef struct Player {
	char name[10];
	CP_Vector pos;
	struct Health hp;
	struct Collider_Circle collider;
	struct Engine engine;
	struct Status status;
	int active;
	int score;
	float speed;
} Player;


struct Player Asteroids_Player_Init(float player_width, float player_height);
void Asteroids_Player_Draw(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);
void Asteroids_Player_Wrap(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);
void Asteroids_Player_Update(Player* player);
void Asteroids_Player_Calculate_Fuel(Player* player);
void Asteroids_Player_Debug(Player player);