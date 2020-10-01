#include "bullet.h"

void init_bullets(struct Bullet arr_bullet[], int count, float bullet_width, float bullet_height)
{
	for (int i = 0; i < count; i++)
	{
		struct Bullet bullet = arr_bullet[i];
		bullet.active = 0;
		bullet.pos = CP_Vector_Set(-1, -1);
		bullet.velocity = CP_Vector_Set(0, 0);

		bullet.collider.width = bullet_width;
		bullet.collider.height = bullet_height;

		arr_bullet[i] = bullet;
	}
}