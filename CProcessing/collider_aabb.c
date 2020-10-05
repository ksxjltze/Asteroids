#include "collider_aabb.h"

int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2)
{
	//simple collision
	int is_overlap_x = (pos1.x + collider1.width / 2>= pos2.x - collider2.width / 2 && pos2.x + collider2.width / 2 >= pos1.x - collider1.width / 2);
	int is_overlap_y = (pos1.y + collider1.height / 2 >= pos2.y - collider2.height / 2 && pos2.y + collider2.height / 2 >= pos1.y - collider1.height / 2);

	if (is_overlap_x && is_overlap_y)
		return 1;

	return 0;
}

void debug_draw_collider(struct Collider_AABB collider, CP_Vector pos)
{
	CP_Graphics_DrawRect(pos.x - collider.width/2, pos.y - collider.height /2, collider.width, collider.height);
}
