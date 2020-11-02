#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"
#include "utility.h"

typedef struct Powerups
{
	CP_Image Sprite;
	CP_Vector Vel, pos;
	float width, height;
	int type;
}Powerup;


void Asteroids_Init_Powerups(void);
void Asteroids_Update_Powerups(void);
//void Asteroids_Exit_Powerups(void);
//void Asteroids_Update_Powerup_Movement(void);
void Asteroids_Draw_Powerup(void);
int Asteroids_Generate_Random_Powerup(void);