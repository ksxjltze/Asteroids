#pragma once
#include <stdbool.h>

enum WeaponType {RAILGUN, LASER};

typedef struct Weapons
{
	int id;
	float damage;
	float fire_rate;
	float projectile_speed;
	bool isPiercing;
} Weapon;