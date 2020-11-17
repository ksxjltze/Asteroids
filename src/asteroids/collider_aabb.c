#include "collider_aabb.h"

int Asteroids_Collision_CheckCollision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2)
{
	//simple collision
	int is_overlap_x = (pos1.x + collider1.width / 2>= pos2.x - collider2.width / 2 && pos2.x + collider2.width / 2 >= pos1.x - collider1.width / 2);
	int is_overlap_y = (pos1.y + collider1.height / 2 >= pos2.y - collider2.height / 2 && pos2.y + collider2.height / 2 >= pos1.y - collider1.height / 2);

	if (is_overlap_x && is_overlap_y)
		return 1;

	return 0;
}

void Asteroids_Collision_Debug_AABB_Draw(struct Collider_AABB collider, CP_Vector pos)
{
	CP_Graphics_DrawRect(pos.x - collider.width/2, pos.y - collider.height /2, collider.width, collider.height);
}

//bool Asteroids_Collision_CheckCollision_Circle_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2)
//{
//	// fuck?
//	float collider1.height / 2;
//	collider1.width;
//	
//	collider2.diameter;
//}
