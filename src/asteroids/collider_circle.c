#include "collider_circle.h"

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