#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"

struct powerups {
	CP_Vector pos;
	struct Collider_AABB collider;
	int active;
};