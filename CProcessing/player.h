#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_aabb.h"
#include "status.h"

struct Player {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	struct Status status;
	int active;
};

void init_player(struct Player player, float player_width, float player_height);
void draw_player(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);

