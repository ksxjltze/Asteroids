#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_aabb.h"
#include "status.h"
#include "constants.h"
#include "utility.h"

struct Enemy {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	int active;
	struct Status status;
};

void init_enemies(struct Enemy arr_enemy[], int count, float enemy_width, float enemy_height);