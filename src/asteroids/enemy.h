#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_aabb.h"
#include "collider_circle.h"
#include "status.h"
#include "constants.h"
#include "utility.h"

struct Enemy {
	CP_Vector pos;
	struct Health hp;
	//struct Collider_AABB collider;

	struct Collider_Circle collider;
	int active;
	struct Status status;
};

void Asteroids_Enemy_Init(struct Enemy arr_enemy[], int count, float enemy_width, float enemy_height);
void Asteroids_Enemy_Update(struct Enemy arr_enemy[], int count);
void Asteroids_Enemy_Draw(struct Enemy arr_enemy[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite, CP_Image health_bar_sprite);
void Asteroids_Enemy_Debug(struct Enemy arr_enemy[], int count);