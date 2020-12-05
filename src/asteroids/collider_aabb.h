//---------------------------------------------------------
// file:	collider_aabb.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	AABB collider header file.
//			Handles intitialization and collision detection for AABB colliders.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "cprocessing.h"
#include "collider_circle.h"

struct Collider_AABB {
	float width;
	float height;
};

int Asteroids_Collision_CheckCollision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2);
void Asteroids_Collision_Debug_AABB_Draw(struct Collider_AABB collider, CP_Vector pos);