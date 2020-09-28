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
};