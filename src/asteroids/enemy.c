#include "enemy.h"
#include "particle.h"
#include "powerups.h"
#include "health.h"
#include "collider_aabb.h"
#include "collider_circle.h"
#include "status.h"
#include "constants.h"
#include "utility.h"

static float spawn_timer;

void Asteroids_Enemy_Init(Enemy arr_enemy[], int count, float enemy_width, float enemy_height, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		enemy.collider.diameter = (enemy_width + enemy_height) / 2;

		enemy.active = 0;
		enemy.hp.max = ENEMY_HP;
		enemy.hp.current = enemy.hp.max;

		//temp;
		enemy.pos = CP_Vector_Zero();
		enemy.velocity = CP_Vector_Zero();
		enemy.speed = 0;

		arr_enemy[i] = enemy;

		spawn_timer = ENEMY_SPAWN_TIME;

	}

	Asteroids_Enemy_Init_Spawn(arr_enemy, count, player);

}

void Asteroids_Enemy_Update(Enemy arr_enemy[], int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy* enemy = &arr_enemy[i];
		if (enemy->active == 0)
			continue;

		enemy->pos = CP_Vector_Add(enemy->pos, CP_Vector_Scale(enemy->velocity, CP_System_GetDt()));

		if (enemy->status.hit)
		{
			enemy->status.hit_cooldown -= CP_System_GetDt();
			if (enemy->status.hit_cooldown <= 0)
			{
				enemy->status.hit = 0;
				enemy->status.hit_cooldown = HURT_WINDOW;
			}
		}

		if (enemy->hp.current <= 0) // enemy dies
		{
			enemy->active = 0;
			spawn_particles(enemy->pos, 20);
			Asteroids_Generate_Powerup_On_Enemy_Death(enemy->pos);
		}

	}
}

void Asteroids_Enemy_Debug(Enemy arr_enemy[], int count)
{
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		if (enemy.active)
		{
			CP_Vector target = CP_Vector_Scale(enemy.velocity, enemy.speed);
			Asteroids_Collision_Debug_Circle_Draw(enemy.collider, enemy.pos);
			CP_Graphics_DrawLine(enemy.pos.x, enemy.pos.y, target.x, target.y);
		}

	}
}

void Asteroids_Enemy_Init_Spawn(Enemy arr_enemy[], int count, Player player)
{
	int spawn_count = CP_Random_RangeInt(ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MIN, ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MAX);
	for (int i = 0; i < spawn_count; i++)
	{
		Asteroids_Enemy_Spawn_Static(arr_enemy, count, player);
	}
}

void Asteroids_Enemy_Spawn_Static(Enemy arr_enemy[], int count, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		if (!enemy.active)
		{
			enemy.active = 1;
			enemy.pos = Asteroids_Utility_Generate_Random_Pos();
			while (Asteroids_Collision_CheckCollision_Circle(enemy.collider, enemy.pos, player.collider, player.pos))
			{
				enemy.pos = Asteroids_Utility_Generate_Random_Pos();
			}
			enemy.speed = 0;
			enemy.velocity = CP_Vector_Zero();
			enemy.hp.max = ENEMY_HP;
			enemy.hp.current = enemy.hp.max;

			arr_enemy[i] = enemy;
			return;
		}
	}
}

void Asteroids_Enemy_Spawn(Enemy arr_enemy[], int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		if (!enemy.active)
		{
			enemy.active = 1;
			enemy.pos = Asteroids_Enemy_Random_Pos();
			enemy.speed = Asteroids_Enemy_Random_Speed();
			enemy.velocity = Asteroids_Enemy_Random_Velocity(enemy.pos, enemy.speed);
			enemy.hp.max = ENEMY_HP;
			enemy.hp.current = enemy.hp.max;

			arr_enemy[i] = enemy;
			return;
		}
	}
}

float Asteroids_Enemy_Random_Speed()
{
	return CP_Random_RangeFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
}

void Asteroids_Enemy_Spawn_Timer(Enemy arr_enemy[], int count)
{
	float dt = CP_System_GetDt();
	spawn_timer -= dt;

	if (spawn_timer <= 0)
	{
		spawn_timer = ENEMY_SPAWN_TIME;
		Asteroids_Enemy_Spawn(arr_enemy, count);
	}

}

CP_Vector Asteroids_Enemy_Random_Velocity(CP_Vector pos, float speed)
{
	CP_Vector vec_to_middle = CP_Vector_Zero();
	CP_Vector vec_offset = CP_Vector_Zero();

	float offset = CP_Random_RangeFloat(-ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET, ASTEROIDS_ASTEROID_ENEMY_VELOCITY_OFFSET);
	vec_offset = CP_Vector_Set(offset, offset);

	vec_to_middle = CP_Vector_Subtract(Asteroids_Utility_GetWindowMiddle(), pos);
	vec_to_middle = CP_Vector_Add(vec_to_middle, vec_offset);
	vec_to_middle = CP_Vector_Normalize(vec_to_middle);
	vec_to_middle = CP_Vector_Scale(vec_to_middle, speed);
	
	return vec_to_middle;
	
}

CP_Vector Asteroids_Enemy_Random_Pos()
{
	CP_Vector pos;
	float win_width, win_height;
	win_width = (float)CP_System_GetWindowWidth();
	win_height = (float)CP_System_GetWindowHeight();

	float x = 0, y = 0;

	while (x >= 0 && x < win_width && y >= 0 && y < win_height)
	{
		x = CP_Random_RangeFloat(-SPAWN_OFFSET, win_width + SPAWN_OFFSET);
		y = CP_Random_RangeFloat(-SPAWN_OFFSET, win_height + SPAWN_OFFSET);
	}

	pos.x = x;
	pos.y = y;

	return pos;
}

void Asteroids_Enemy_Draw(Enemy arr_enemy[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite, CP_Image health_bar_sprite)
{
	float offset_y = enemy_height / 2 + BAR_HEIGHT + BAR_OFFSET_Y;
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		if (enemy.active)
		{
			CP_Image_Draw(enemy_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			float percent = enemy.hp.current / enemy.hp.max;
			CP_Image_Draw(health_bar_sprite, enemy.pos.x, enemy.pos.y - offset_y, percent * BAR_WIDTH, BAR_HEIGHT, 255);

			if (enemy.status.hit)
			{
				CP_Image_Draw(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			}
		}
	}
}
