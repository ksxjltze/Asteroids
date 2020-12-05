//---------------------------------------------------------
// file:	weapon.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Weapon data header file.
//			Provides the Weapon struct and types.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <stdbool.h>

enum WeaponType {RAILGUN, LASER};

typedef struct Specials
{
	bool homing;
	bool swarm;
}Special;

typedef struct Weapons
{
	int id;
	float damage;
	float fire_rate;
	float projectile_speed;
	int projectile_count;
	Special special;
	bool isPiercing;
} Weapon;