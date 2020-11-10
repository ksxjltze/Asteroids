#pragma once
#include "cprocessing.h"
#include "collider_circle.h"
#include "utility.h"
#include <stdbool.h>
#include <stdio.h>
#include"player.h"
#include "powerup_interaction.h"

typedef struct Powerups
{
	struct Collider_Circle collider;
	CP_Vector movement_Vel, pos;
	float rotation;
	int type;
	bool active;
}Powerup;


// GENERAL
void Asteroids_Init_Powerups(void);
void Asteroids_Update_Powerups(struct Player* player);

//DRAWING POWERUPS
void Asteroids_Draw_Powerup(int type, CP_Vector* pos, CP_Vector movement_vel, float* rotation);

// UTILITY 
int Asteroids_Generate_Random_Powerup(void);
int Asteroids_Powerup_RNG(void);

// Asteroid death powerups 
void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position);

// Floating time based powerups
void Asteroids_Floating_Powerup_Lifespan_Manager(void);
void Asteroids_Floating_Powerup_Manager(void);


// COLLISION
void Asteroids_Powerup_Player_Collision(Powerup powerup_pool[], struct Player* player);
void Asteroids_Powerup_Interact_Fuel_Pickup(Player* player);

