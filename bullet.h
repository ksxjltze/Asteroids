#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"
#include "collider_circle.h"
#include "constants.h"
#include "enemy.h"
#include "collision_manager.h"

struct Bullet {
	CP_Vector pos;
	struct Collider_Circle collider;
	CP_Vector velocity;
	int active;
};

void init_bullets(struct Bullet arr_bullet[], int count, float bullet_width, float bullet_height);
void process_bullets(struct Bullet arr_bullet[], int bullet_count, struct Enemy arr_enemy[], int enemy_count);
void draw_bullets(struct Bullet arr_bullet[], int count, CP_Image bullet_sprite, float bullet_width, float bullet_height);
void debug_bullets(struct Bullet arr_bullet[], int count);