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

struct Enemy {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	int active;
	struct Status status;
};

struct Player {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	struct Status status;
};