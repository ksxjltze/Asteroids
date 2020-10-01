#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_aabb.h"
#include "status.h"

void init_player();
void draw_player(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation);

struct Player {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	struct Status status;
	int active;
};