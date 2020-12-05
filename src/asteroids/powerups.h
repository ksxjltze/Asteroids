#pragma once
//---------------------------------------------------------
// file:	powerup.h
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the powerups.
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "collider_circle.h"
#include "utility.h"
#include <stdbool.h>
#include <stdio.h>
#include "player.h"
#include "powerup_interaction.h"
#include "constants.h"

typedef struct Powerups
{
	struct Collider_Circle collider;
	CP_Vector movement_Vel, pos;
	float rotation, current_lifespan;
	int type;
	bool active, effect;
}Powerup;

// Function which initialize powerup variables on game launch
void Asteroids_Init_Powerups(void);

// Function which handles update every frame
void Asteroids_Update_Powerups(struct Player* player);

// Function which handles the drawing of powerups
void Asteroids_Draw_Powerup(int type, CP_Vector* pos, CP_Vector movement_vel, float* rotation);

// UTILITY: 
int Asteroids_Generate_Random_Powerup(void);
int Asteroids_Powerup_RNG(void);
void Asteroids_Checkpowerup_Location(Powerup* powerup);
void Asteroids_Powerup_Reset(Powerup* powerup);

// Spawn powerup on asteroid death 
void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position);

// Manages the 
void Asteroids_Floating_Powerup_Lifespan_Manager(void);

// Tracks the powerup effect lifespan.
void Asteroids_Powerup_Lifespan_Manager(Powerup* powerup);

// Function which spawns a random floating powerup
void Asteroids_Spawn_Floating_Powerup(void);


// COLLISION
void Asteroids_Powerup_Player_Collision(Powerup powerup_pool[], struct Player* player);

// INTERACTION
void Asteroids_Powerup_Interact_Fuel_Pickup(Player* player);
void Asteroids_Pickup_Interact_Hp(Player* player);


