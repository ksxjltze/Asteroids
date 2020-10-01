#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"

struct Bullet {
	CP_Vector pos;
	struct Collider_AABB collider;
	CP_Vector velocity;
	int active;
};

void init_bullets(struct Bullet arr_bullet[], int count, float bullet_width, float bullet_height);