#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"
#include "utility.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Powerups
{
	CP_Image Sprite;
	CP_Vector Movement_Vel, pos;
	float width, height;
	int type;
}Powerup;


void Asteroids_Init_Powerups(void);
void Asteroids_Update_Powerups(void);
void Asteroids_Draw_Powerup(void);


int Asteroids_Generate_Random_Powerup(void);

// Asteroid death powerups 
void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position);

// Floating time based powerups
void Asteroids_Floating_Powerup_Time_Manager(void);
void Asteroids_Floating_Powerup_Manager(void);