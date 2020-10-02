#include "collider_aabb.h"

int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2)
{
	//simple collision
	int is_overlap_x = (pos1.x >= pos2.x - collider2.width / 2 && pos2.x + collider2.width / 2 >= pos1.x);
	int is_overlap_y = (pos1.y >= pos2.y - collider2.height / 2 && pos2.y + collider2.height / 2 >= pos1.y);

	if (is_overlap_x && is_overlap_y)
		return 1;

	return 0;
}