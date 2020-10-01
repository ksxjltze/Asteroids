#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"
#include "constants.h"
#include "enemy.h"

struct Bullet {
	CP_Vector pos;
	struct Collider_AABB collider;
	CP_Vector velocity;
	int active;
};

void init_bullets(struct Bullet arr_bullet[], int count, float bullet_width, float bullet_height);
void process_bullets(struct Bullet arr_bullet[], int bullet_count, struct Enemy arr_enemy[], int enemy_count);
void draw_bullets(struct Bullet arr_bullet[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height);