#pragma once
#include "cprocessing.h"

struct Collider_Circle
{
	float diameter;
};

int Asteroids_Collision_CheckCollision_Circle(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2);
void Asteroids_Collision_Debug_Circle_Draw(struct Collider_Circle collider, CP_Vector pos);