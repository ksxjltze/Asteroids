#pragma once
#include "cprocessing.h"

struct Collider_AABB {
	float width;
	float height;
};

int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2);
void debug_draw_collider_rect(struct Collider_AABB collider, CP_Vector pos);