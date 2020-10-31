#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_aabb.h"
#include "status.h"
#include "engine.h"

struct Player {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	struct Engine engine;
	struct Status status;
	int active;
	float speed;
};


struct Player init_player(float player_width, float player_height);
void draw_player(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);
void player_wrap(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);
void update_player(struct Player* player);
void calculate_fuel(struct Player* player);
void debug_player(struct Player player);
