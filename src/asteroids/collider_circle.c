#include "collider_circle.h"

int check_collision_circle(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_Circle collider2, CP_Vector pos2)
{
	float distance = CP_Vector_Distance(pos1, pos2);
	if (distance <= collider1.diameter / 2+ collider2.diameter / 2)
		return 1;
	
	return 0;
}

void debug_draw_collider_circle(struct Collider_Circle collider, CP_Vector pos)
{
	CP_Graphics_DrawCircle(pos.x, pos.y, collider.diameter);
}