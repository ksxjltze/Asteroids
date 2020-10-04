#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_aabb.h"
#include "status.h"

struct Fuel
{
	float current;
	float max;
};

struct Engine
{
	struct Fuel fuel;
	float drain_rate; //per second
};

struct Player {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	struct Engine engine;
	struct Status status;
	int active;
};


struct Player init_player(struct Player player, float player_width, float player_height);
void draw_player(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);
void update_player(struct Player* player);
void calculate_fuel(struct Player* player);
