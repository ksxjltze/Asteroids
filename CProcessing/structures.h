#pragma once
struct Collider_AABB {
	int width;
	int height;
};

struct Bullet {
	CP_Vector pos;
	struct Collider_AABB collider;
	CP_Vector velocity;
	int active;
};

struct Health {
	float current;
	float max;
};

struct Status {
	int hit;
	float hit_cooldown;
};