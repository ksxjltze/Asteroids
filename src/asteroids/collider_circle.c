//---------------------------------------------------------
// file:	collider_circle.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Circle collider source file.
//			Handles intitialization and collision detection for circle colliders.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "collider_circle.h"

struct Collider_Circle Asteroids_Collision_Circle_Init_Collider(float diameter)
{
	struct Collider_Circle collider;
	collider.diameter = diameter;
	collider.enabled = true;
	return collider;
}

int Asteroids_Collision_CheckCollision_Circle(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2)
{
	float distance = CP_Vector_Distance(pos1, pos2);
	if (distance <= collider1.diameter / 2+ collider2.diameter / 2)
		return 1;
	
	return 0;
}

void Asteroids_Collision_Debug_Circle_Draw(struct Collider_Circle collider, CP_Vector pos)
{
	CP_Graphics_DrawCircle(pos.x, pos.y, collider.diameter);
}

bool Asteroids_Collision_CheckCollision_Circle_Test(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2)
{
	float distance = CP_Vector_Distance(pos1, pos2);
	if (distance <= collider1.diameter / 2 + collider2.diameter / 2) 
		return true;

	return false;
}