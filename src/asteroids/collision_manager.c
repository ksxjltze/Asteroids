#include "collision_manager.h"
#include "powerups.h"
#include "powerup_interaction.h"

extern bool invulnerable;

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

			Asteroids_Enemy_Hit(enemy, BULLET_DAMAGE);

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
				if (!invulnerable)
				{
					Asteroids_Player_Hit(player, enemy->size * ASTEROIDS_ASTEROID_ENEMY_BASE_DAMAGE);
				}
				Asteroids_Enemy_Death(enemy);
				return;
			}

	}
}

void Asteroids_Collision_CheckCollision_Enemy_Enemy(Enemy enemy_pool[], int enemy_count, Enemy* enemy, Player player)
{
	for (int i = 0; i < enemy_count; i++)
	{
		if (enemy_pool[i].active)
		{
			if (enemy_pool[i].id == enemy->id)
				continue;
			else if (Asteroids_Collision_CheckCollision_Circle(enemy_pool[i].collider, enemy_pool[i].pos, enemy->collider, enemy->pos))
			{
				Asteroids_Enemy_Collide(&enemy_pool[i], enemy, enemy_pool, enemy_count, player);
				return;
			}

		}

	}
}

bool Asteroids_Collision_CheckCollision_AABB_Circle(struct Collider_AABB aabb, CP_Vector aabb_pos, struct Collider_Circle circle, CP_Vector circle_pos)
{
	CP_Vector difference = CP_Vector_Subtract(circle_pos, aabb_pos);
	CP_Vector clamped = CP_Vector_Zero();

	clamped.x = CP_Math_ClampFloat(difference.x, -(aabb.width / 2), aabb.width / 2);
	clamped.y = CP_Math_ClampFloat(difference.y, -(aabb.height / 2), aabb.height / 2);

	CP_Vector closest = CP_Vector_Add(aabb_pos, clamped);
	difference = CP_Vector_Subtract(closest, circle_pos);

	return CP_Vector_Length(difference) < (circle.diameter / 2);
}