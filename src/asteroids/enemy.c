#include "enemy.h"
#include "particle.h"

void Asteroids_Enemy_Init(Enemy arr_enemy[], int count, float enemy_width, float enemy_height)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		enemy.collider.diameter = (enemy_width + enemy_height) / 2;

		enemy.active = 0;
		enemy.hp.max = ENEMY_HP;
		enemy.hp.current = enemy.hp.max;

		//temp;
		enemy.pos = Asteroids_Utility_Generate_Random_Pos();
		enemy.velocity = Asteroids_Enemy_Random_Velocity(enemy.pos);

		arr_enemy[i] = enemy;

	}

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

		if (enemy->hp.current <= 0)
		{
			enemy->active = 0;
			spawn_particles(enemy->pos, 20);
		}

	}
}

void Asteroids_Enemy_Debug(Enemy arr_enemy[], int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemy[i];
		if (enemy.active)
		{
			//Asteroids_Collision_Debug_AABB_Draw(enemy.collider, enemy.pos);
			Asteroids_Collision_Debug_Circle_Draw(enemy.collider, enemy.pos);
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
			enemy.velocity = Asteroids_Enemy_Random_Velocity(enemy.pos);
			enemy.hp.max = ENEMY_HP;
			enemy.hp.current = enemy.hp.max;

			arr_enemy[i] = enemy;
			return;
		}
	}
}

CP_Vector Asteroids_Enemy_Random_Velocity(CP_Vector pos)
{
	CP_Vector vec_to_middle;
	//CP_Vector velocity;

	//TODO, better implementation
	vec_to_middle = CP_Vector_Subtract(Asteroids_Utility_GetWindowMiddle(), pos);
	return vec_to_middle;
	
}

CP_Vector Asteroids_Enemy_Random_Pos()
{
	CP_Vector pos;
	int win_width, win_height;
	win_width = (int)CP_System_GetWindowWidth();
	win_height = (int)CP_System_GetWindowHeight();

	int x, y;

	x = CP_Random_RangeInt(0, win_width * 2) - win_width;
	y = CP_Random_RangeInt(0, win_height * 2) - win_height;

	while (x % win_width == x ||  y % win_height == y)
	{
		x = CP_Random_RangeInt(0, win_width * 2) - win_width;
		y = CP_Random_RangeInt(0, win_height * 2) - win_height;
	}

	pos.x = (float)x;
	pos.y = (float)y;

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
