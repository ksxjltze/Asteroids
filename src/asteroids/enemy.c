#include "enemy.h"
#include "particle.h"
#include "powerups.h"
#include "health.h"
#include "collider_circle.h"
#include "status.h"
#include "constants.h"
#include "utility.h"
#include "score.h"
#include "collision_manager.h"

static float spawn_timer;

void Asteroids_Enemy_Init(Enemy enemy_pool[], int count, float enemy_width, float enemy_height, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = enemy_pool[i];
		enemy.collider.diameter = (enemy_width + enemy_height) / 2;
		enemy.id = i + 1;

		enemy.active = 0;
		enemy.hp.max = ENEMY_HP;
		enemy.hp.current = enemy.hp.max;

		//temp;
		enemy.pos = CP_Vector_Zero();
		enemy.velocity = CP_Vector_Zero();
		enemy.speed = 0;
		enemy.rotation = 0;
		enemy.rotate_rate = CP_Random_RangeFloat(ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MIN, ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MAX);

		enemy_pool[i] = enemy;

		spawn_timer = ENEMY_SPAWN_TIME;

	}

	Asteroids_Enemy_Init_Spawn(enemy_pool, count, player);

}


void Asteroids_Enemysplit_Init_Spawn(Enemy arr_enemysplit[], int count, Player player)
{
	int spawn_count = CP_Random_RangeInt(ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MIN, ASTEROIDS_ASTEROID_ENEMYSPLIT_SPAWN_COUNT_MAX);
	for (int i = 0; i < spawn_count; i++)
	{
		Asteroids_Enemy_Spawn_Static(arr_enemysplit, count, player);
	}
}


void Asteroids_Enemysplit_Spawn(Enemy arr_enemysplit[], int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemysplit[i];
		if (!enemy.active)
		{
			enemy.active = 1;
			enemy.pos = Asteroids_Enemy_Random_Pos();
			enemy.speed = Asteroids_Enemy_Random_Speed();
			enemy.velocity = Asteroids_Enemy_Random_Velocity(enemy.pos, enemy.speed);
			enemy.hp.max = ENEMY_HP;
			enemy.hp.current = enemy.hp.max;

			arr_enemysplit[i] = enemy;
			return;
		}
	}
}


void Asteroids_Enemy_Update(Enemy enemy_pool[], int count, Player player)
{
	float dt = CP_System_GetDt();
	for (int i = 0; i < count; i++)
	{
		Enemy* enemy = &enemy_pool[i];
		if (enemy->active == 0)
			continue;

		enemy->pos = CP_Vector_Add(enemy->pos, CP_Vector_Scale(enemy->velocity, dt));
		Asteroids_Enemy_Idle_Rotate(enemy, enemy->rotate_rate, dt);
		Asteroids_Collision_CheckCollision_Enemy_Enemy(enemy_pool, count, &enemy_pool[i]);

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
			Score.enemy_kill_score += 1;
			enemy->active = 0;
			spawn_particles(enemy->pos, 8, 0, 0);
			Asteroids_Generate_Powerup_On_Enemy_Death(enemy->pos);
			Asteroids_Enemysplit_Init_Spawn(enemy_pool, 100 , player);
			Asteroids_Enemysplit_Spawn(enemy_pool,2);


		}
	//		Asteroids_Enemy_Death(enemy);
		

	}
}

void Asteroids_Enemy_Death(Enemy* enemy)
{
	Score.enemy_kill_score += 1;
	enemy->active = 0;
	spawn_particles(enemy->pos, 8, 0, 0);
	Asteroids_Generate_Powerup_On_Enemy_Death(enemy->pos);
}

void Asteroids_Enemy_Debug(Enemy enemy_pool[], int count)
{
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = enemy_pool[i];
		if (enemy.active)
		{
			CP_Vector target = CP_Vector_Scale(enemy.velocity, enemy.speed);
			Asteroids_Collision_Debug_Circle_Draw(enemy.collider, enemy.pos);
			CP_Graphics_DrawLine(enemy.pos.x, enemy.pos.y, target.x, target.y);
		}

	}
}

void Asteroids_Enemy_Init_Spawn(Enemy enemy_pool[], int count, Player player)
{
	int spawn_count = CP_Random_RangeInt(ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MIN, ASTEROIDS_ASTEROID_ENEMY_SPAWN_COUNT_MAX);
	for (int i = 0; i < spawn_count; i++)
	{
		Asteroids_Enemy_Spawn_Static(enemy_pool, count, player);
	}
}

void Asteroids_Enemy_Spawn_Static(Enemy enemy_pool[], int count, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = enemy_pool[i];
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

			enemy_pool[i] = enemy;
			return;
		}
	}
}

void Asteroids_Enemy_Spawn(Enemy enemy_pool[], int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = enemy_pool[i];
		if (!enemy.active)
		{
			enemy.active = 1;
			enemy.pos = Asteroids_Enemy_Random_Pos();
			enemy.speed = Asteroids_Enemy_Random_Speed();
			enemy.velocity = Asteroids_Enemy_Random_Velocity(enemy.pos, enemy.speed);
			enemy.hp.max = ENEMY_HP;
			enemy.hp.current = enemy.hp.max;

			enemy_pool[i] = enemy;
			return;
		}
	}
}

float Asteroids_Enemy_Random_Speed()
{
	return CP_Random_RangeFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
}

void Asteroids_Enemy_Spawn_Timer(Enemy enemy_pool[], int count)
{
	float dt = CP_System_GetDt();
	spawn_timer -= dt;

	if (spawn_timer <= 0)
	{
		spawn_timer = ENEMY_SPAWN_TIME;
		Asteroids_Enemy_Spawn(enemy_pool, count);
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

void Asteroids_Enemy_Draw(Enemy enemy_pool[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = enemy_pool[i];
		if (enemy.active)
		{
			CP_Image_DrawAdvanced(enemy_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255, enemy.rotation);

			if (enemy.status.hit)
			{
				CP_Image_DrawAdvanced(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255, enemy.rotation);
			}
		}
	}
}

void Asteroids_Enemy_Idle_Rotate(Enemy* enemy, float rotate_rate, float dt)
{
	enemy->rotation += rotate_rate * dt;
}

void Asteroids_Enemy_Collide(Enemy* enemy1, Enemy* enemy2)
{
	Asteroids_Enemy_Death(enemy1);
	Asteroids_Enemy_Death(enemy2);
}


//LIU KE

void Asteroids_Enemysplit_Init(Enemy arr_enemysplit[], int count, float enemy_width, float enemy_height, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemysplit[i];
		enemy.collider.diameter = (enemy_width + enemy_height) / 2;

		enemy.active = 0;
		enemy.hp.max = ENEMY_HP/(float)2;
		enemy.hp.current = enemy.hp.max;

		//temp;
		enemy.pos = CP_Vector_Zero();
		enemy.velocity = CP_Vector_Zero();
		enemy.speed = 0;

		arr_enemysplit[i] = enemy;

		spawn_timer = ENEMY_SPAWN_TIME;

	}

	void Asteroids_Enemysplit_Init_Spawn(Enemy arr_enemysplit[], int count, Player player);

}

void Asteroids_Enemysplit_Update(Enemy arr_enemysplit[], int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy* enemy = &arr_enemysplit[i];
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
			spawn_particles(enemy->pos, 20, 0, 0);
			Asteroids_Generate_Powerup_On_Enemy_Death(enemy->pos);
		}

	}
}


void Asteroids_Enemysplit_Draw(Enemy arr_enemysplit[], int count, CP_Image enemy_sprite, float enemy_width, float enemy_height, CP_Image enemy_hurt_sprite, CP_Image health_bar_sprite)
{
	float offset_y = enemy_height / 2 + BAR_HEIGHT + BAR_OFFSET_Y;
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemysplit[i];
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





void Asteroids_Enemysplit_Spawn_Static(Enemy arr_enemysplit[], int count, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = arr_enemysplit[i];
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

			arr_enemysplit[i] = enemy;
			return;
		}
	}
}




void Asteroids_Enemysplit_Spawn_Timer(Enemy arr_enemysplit[], int count)
{
	float dt = CP_System_GetDt();
	spawn_timer -= dt;

	if (spawn_timer <= 0)
	{
		spawn_timer = ENEMY_SPAWN_TIME;
		Asteroids_Enemy_Spawn(arr_enemysplit, count);
	}

}
