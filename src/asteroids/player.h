//---------------------------------------------------------
// file:	player.h
// author:	Lee Jia Keat
// contributors: Dania Mohd (Particle Effects and Animation)
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Player entity header file.
//			Contains functions for player functionality.
//			Defines the player entity struct.
//			Initializes, Draws and Updates a specified player entity.
//			Handles player movement and fuel management.
//			Provides an interface for damaging and disabling the player entity.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"
#include "health.h"
#include "collider_circle.h"
#include "status.h"
#include "engine.h"
#include <string.h>
#include "weapon.h" 

typedef struct Player {
	struct Engine engine;
	Weapon weapon;
	struct Status status;
	struct Health hp;
	struct Collider_Circle collider;
	CP_Vector pos;
	CP_Vector velocity;
	float speed;
	int active;
	char name[20];
	int score;
	float bullet_diameter;
	int alpha;
	float rotation;
} Player;


struct Player Asteroids_Player_Init(float player_width, float player_height, bool is_apply_ugprades);
void Asteroids_Player_Update(Player* player);	//DANIA

void Asteroids_Player_Draw(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, int player_alpha, float player_rotation);

void Asteroids_Player_Calculate_Fuel(Player* player);
void Asteroids_Player_Drain_Fuel(Player* player);
void Asteroids_Player_Refuel(float amount, Player* player);

void Asteroids_Player_Debug(Player player);

void Asteroids_Player_Update_Movement(Player* player, float dt);
void Asteroids_Player_Simple_Movement(Player* player);
void Asteroids_Player_Check_Input(Player* player, float dt, CP_Vector direction);

void Asteroids_Player_Accelerate(Player* player, float dt, CP_Vector direction);
void Asteroids_Player_Decelerate(Player* player, float dt);
void Asteroids_Player_Strafe_Port(Player* player, float dt, CP_Vector direction);
void Asteroids_Player_Strafe_Starboard(Player* player, float dt, CP_Vector direction);

void Asteroids_Player_Death(Player* player);
void Asteroids_Player_Hit(Player* player, float damage);