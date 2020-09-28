#pragma once
#include "structures.h"
#include "cprocessing.h"

struct Player {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	struct Status status;
};