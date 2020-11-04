#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"
#include "utility.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Powerups
{
	struct Collider_AABB collider;
	CP_Vector movement_Vel, pos;
	float rotation;
	int type;
	bool active;
}Powerup;


void Asteroids_Init_Powerups(void);
void Asteroids_Update_Powerups(void);


int Asteroids_Generate_Random_Powerup(void);

void Asteroids_Draw_Powerup(int type, CP_Vector* pos, CP_Vector movement_vel, float* rotation);

// Asteroid death powerups 
void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position);

// Floating time based powerups
void Asteroids_Floating_Powerup_Lifespan_Manager(void);
void Asteroids_Floating_Powerup_Manager(void);