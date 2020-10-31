#pragma once
#include "cprocessing.h"

struct Collider_Circle
{
	float diameter;
};

int check_collision_circle(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2);
void debug_draw_collider_circle(struct Collider_Circle collider, CP_Vector pos);