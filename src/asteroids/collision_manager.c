#include "collision_manager.h"

int Asteroids_Collision_CheckCollision_Circle_AABB(struct Collider_Circle collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2)
{
	return 0;
}

struct Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy arr_enemy[], int enemy_count, struct Bullet bullet)
{
	for (int j = 0; j < enemy_count; j++)
	{
		if (!arr_enemy[j].active)
			continue;

		Enemy* enemy = &arr_enemy[j];
		if (Asteroids_Collision_CheckCollision_Circle(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
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

void Asteroids_Collision_CheckCollision_Enemy_Player(Enemy arr_enemy[], int enemy_count, Player* player)
{
	for (int i = 0; i < enemy_count; i++)
	{
		if (!arr_enemy[i].active)
			continue;

		Enemy* enemy = &arr_enemy[i];
		if (Asteroids_Collision_CheckCollision_Circle(enemy->collider, enemy->pos, player->collider, player->pos))
		{
			//player->active = 0;
			if (!player->status.hit)
			{
				player->hp.current -= 1;
				player->status.hit = 1;
			}
			enemy->active = 0;
			return;

		}

	}
}
