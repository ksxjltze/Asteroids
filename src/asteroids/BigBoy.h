#pragma once
#include "cprocessing.h"
#include "player.h"
#include "game.h"

typedef struct BigBoys {
	CP_Vector pos;
	CP_Vector velocity;
	float speed;
	float rotation;
	float rotate_rate;

	float size;
	struct Health hp;
	struct Collider_Circle collider;
	struct Status status;

	int active;
	int split_count;

	int id;
	int parent_id;
} BigBoy;