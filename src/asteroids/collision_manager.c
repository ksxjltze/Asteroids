#include "collision_manager.h"
#include "collider_circle.h"

Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy enemy_pool[], int enemy_count, Bullet bullet)
{
	for (int j = 0; j < enemy_count; j++)
	{
		if (!enemy_pool[j].active)
			continue;

		Enemy* enemy = &enemy_pool[j];
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

void Asteroids_Collision_CheckCollision_Enemy_Player(Enemy enemy_pool[], int enemy_count, Player* player)
{
	for (int i = 0; i < enemy_count; i++)
	{
		if (!enemy_pool[i].active)
			continue;

		Enemy* enemy = &enemy_pool[i];
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

void Asteroids_Collision_CheckCollision_Enemy_Enemy(Enemy enemy_pool[], int enemy_count, Enemy* enemy)
{
	for (int i = 0; i < enemy_count; i++)
	{
		if (enemy_pool[i].active)
		{
			if (enemy_pool[i].id == enemy->id)
				continue;
			else if (Asteroids_Collision_CheckCollision_Circle(enemy_pool[i].collider, enemy_pool[i].pos, enemy->collider, enemy->pos))
			{
				Asteroids_Enemy_Collide(&enemy_pool[i], enemy);
				return;
			}

		}

	}
}
