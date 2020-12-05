//---------------------------------------------------------
// file:	collision_manager.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Collision Manager source file.
//			Checks and resolves specific collisions between various entities.
//			Detects collision between two colliders. (AABB and Circle)
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "collision_manager.h"
#include "powerups.h"
#include "powerup_interaction.h"
#include <stdio.h>
#include "audio_manager.h"

extern bool invulnerable;

typedef struct Collision
{
	int colliderA_id;
	int colliderB_id;
} Collision;

Collision* collisions;
static unsigned int collision_counter;

void Asteroids_Collision_Init()
{
	collisions = NULL;
	collision_counter = 0;
}

Bullet Asteroids_Collision_CheckCollision_Enemy_Bullet(Enemy enemy_pool[], int enemy_count, Bullet bullet, Player player)
{
	for (int j = 0; j < enemy_count; j++)
	{
		if (!enemy_pool[j].active)
			continue;

		Enemy* enemy = &enemy_pool[j];
		if (Asteroids_Collision_CheckCollision_Circle(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
		{
			for (unsigned int i = 0; i < collision_counter; i++)
			{
				if (collisions[i].colliderA_id == bullet.id && collisions[i].colliderB_id == enemy->id)
				{
					return bullet;
				}
			}
			bullet = Asteroids_Collision_EnterCollision_Enemy_Bullet(bullet, enemy, player);
			return bullet;
		}
		else
		{
			for (unsigned int i = 0; i < collision_counter; i++)
			{
				if (collisions[i].colliderA_id == bullet.id && collisions[i].colliderB_id == enemy->id)
				{
					Asteroids_Collision_ExitCollision_Enemy_Bullet(bullet, enemy, player, i);
					return bullet;
				}
			}

		}
	}
	return bullet;
}

Bullet Asteroids_Collision_EnterCollision_Enemy_Bullet(Bullet bullet, Enemy* enemy, Player player)
{
	Collision* temp = realloc(collisions, ++collision_counter * sizeof(Collision));
	if (temp != NULL)
	{
		collisions = temp;
		collisions[collision_counter - 1].colliderA_id = bullet.id;
		collisions[collision_counter - 1].colliderB_id = enemy->id;

		if ((!player.weapon.isPiercing && bullet.type == LINEAR_PROJECTILE) || (bullet.type == HOMING_PROJECTILE && !player.weapon.special.swarm))
		{
			bullet.active = 0;
			bullet.pos = CP_Vector_Set(-1, -1);
			bullet.velocity = CP_Vector_Set(0, 0);
		}
		Asteroids_Enemy_Hit(enemy, player.weapon.damage);
		return bullet;
	}
	printf("ERROR: Failed to allocate memory for new collision.\n");
	return bullet;

}

Bullet Asteroids_Collision_ExitCollision_Enemy_Bullet(Bullet bullet, Enemy* enemy, Player player, int collisionID)
{
	for (unsigned int i = collisionID; i < collision_counter; i++)
	{
		collisions[i] = collisions[i + 1];
	}

	Collision* temp = realloc(collisions, sizeof(Collision) * --collision_counter);
	collisions = temp;
	return bullet;
}

void Asteroids_Collision_Exit()
{
	if (collisions)
	{
		free(collisions);
		collisions = NULL;
		collision_counter = 0;
	}
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
	if (DIFFICULTY_OPTION >= IMPOSSIBLE)
		return;

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