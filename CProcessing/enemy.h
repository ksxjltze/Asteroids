#pragma once
#include "cprocessing.h"
#include "structures.h"

struct Enemy {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	int active;
	struct Status status;
};