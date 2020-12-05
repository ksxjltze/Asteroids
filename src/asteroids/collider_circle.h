//---------------------------------------------------------
// file:	collider_circle.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Circle collider header file.
//			Handles intitialization and collision detection for circle colliders.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"
#include <stdbool.h>

struct Collider_Circle
{
	float diameter;
	bool enabled;
};

struct Collider_Circle Asteroids_Collision_Circle_Init_Collider(float diameter);

int Asteroids_Collision_CheckCollision_Circle(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2);
void Asteroids_Collision_Debug_Circle_Draw(struct Collider_Circle collider, CP_Vector pos);

bool Asteroids_Collision_CheckCollision_Circle_Test(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2);