#include "collision_manager.h"

struct Bullet check_collision_enemy_bullet(struct Enemy arr_enemy[], int enemy_count, struct Bullet bullet)
{
	for (int j = 0; j < enemy_count; j++)
	{
		if (!arr_enemy[j].active)
			continue;

		struct Enemy* enemy = &arr_enemy[j];
		if (check_collision_AABB(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
		{
			bullet.active = 0;
			bullet.pos = CP_Vector_Set(-1, -1);
			bullet.velocity = CP_Vector_Set(0, 0);

			if (!enemy->status.hit)
			{
				enemy->status.hit = 1;
				enemy->hp.current -= BULLET_DAMAGE;
			}

			return bullet;
		}
	}
	return bullet;
}
