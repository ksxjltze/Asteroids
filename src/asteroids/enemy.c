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
static float spawn_interval;
void Asteroids_Enemy_Init(Enemy enemy_pool[], int count, float enemy_width, float enemy_height, Player player)
{
	for (int i = 0; i < count; i++)
	{
		Enemy enemy = enemy_pool[i];
		enemy.collider.diameter = (enemy_width + enemy_height)/2;
		enemy.id = i + 1;

		enemy.active = 0;
		enemy.hp.max = 0;
		enemy.hp.current = 0;

		enemy.pos = CP_Vector_Zero();
		enemy.velocity = CP_Vector_Zero();
		enemy.speed = 0;
		enemy.rotation = 0;
		enemy.size = 0;
		enemy.rotate_rate = 0;
		enemy.parent_id = 0;
		enemy.split_count = 0;

		enemy_pool[i] = enemy;

		spawn_interval = ASTEROIDS_ENEMY_BASE_SPAWN_INTERVAL;
		spawn_timer = spawn_interval;

	}

	Asteroids_Enemy_Init_Spawn(enemy_pool, count, player);

}

void Asteroids_Enemy_Update(Enemy enemy_pool[], int count, Player player)
{
	float dt = CP_System_GetDt();
	for (int i = 0; i < count; i++)
	{
		Enemy* enemy = &enemy_pool[i];
		if (enemy->active)
		{
			enemy->pos = CP_Vector_Add(enemy->pos, CP_Vector_Scale(enemy->velocity, dt));
			Asteroids_Enemy_Idle_Rotate(enemy, enemy->rotate_rate, dt);
			Asteroids_Collision_CheckCollision_Enemy_Enemy(enemy_pool, count, &enemy_pool[i], player);
			Asteroids_Enemy_Check_OutOfBounds(enemy_pool, count);

			if (enemy->status.hit)
			{
				enemy->status.hit_cooldown -= CP_System_GetDt();
				if (enemy->status.hit_cooldown <= 0)
				{
					enemy->status.hit = 0;
					enemy->status.hit_cooldown = HURT_WINDOW;
				}
			}

			if (enemy->hp.current < 0) // enemy dies
			{
				Asteroids_Enemy_Split(enemy, player, enemy_pool, count);
				Asteroids_Enemy_Death(enemy);
			}

		}

	}
}

void Asteroids_Enemy_Check_OutOfBounds(Enemy enemy_pool[], int pool_size)
{
	for (int i = 0; i < pool_size; i++)
	{
		if (!enemy_pool[i].active)
			continue;

		if ((enemy_pool[i].pos.x > CP_System_GetWindowWidth() + ASTEROIDS_ENEMY_SPAWN_OFFSET) || (enemy_pool[i].pos.x < 0 - ASTEROIDS_ENEMY_SPAWN_OFFSET) || (enemy_pool[i].pos.y > CP_System_GetWindowHeight() + ASTEROIDS_ENEMY_SPAWN_OFFSET) || (enemy_pool[i].pos.y < 0 - ASTEROIDS_ENEMY_SPAWN_OFFSET))
		{
			Asteroids_Enemy_Reset(&enemy_pool[i]);
		}
	}
}

void Asteroids_Enemy_Split(Enemy* enemy, Player player, Enemy enemy_pool[], int count)
{
	if (enemy->split_count < ASTEROIDS_ENEMY_SPLIT_MAX_COUNT)
	{
		if (enemy->collider.diameter > player.bullet_diameter)
		{
			unsigned int split_count = CP_Random_RangeInt(ASTEROIDS_ENEMY_SPLIT_MIN_NUMBER, ASTEROIDS_ENEMY_SPLIT_MAX_NUMBER);
			for (unsigned int j = 0; j < split_count; j++)
			{
				Asteroids_Enemy_Spawn_Child(enemy_pool, count, *enemy, split_count);
			}
		}
	}
}

void Asteroids_Enemy_Death(Enemy* enemy)
{
	Score.enemy_kill_score += 1;
	int random = Asteroids_Powerup_RNG();
	if (random <= 2)
	{
		Asteroids_Generate_Powerup_On_Enemy_Death(enemy->pos);
	}
	spawn_particles(enemy->pos, 8, 0, 0, enemy->size);
	Asteroids_Enemy_Reset(enemy);
}

void Asteroids_Enemy_Reset(Enemy* enemy)
{
	enemy->active = 0;
	enemy->hp.max = 0;
	enemy->hp.current = 0;
	enemy->collider.diameter = 0;

	enemy->pos = CP_Vector_Zero();
	enemy->velocity = CP_Vector_Zero();
	enemy->speed = 0;
	enemy->rotation = 0;
	enemy->size = 0;
	enemy->rotate_rate = 0;
	enemy->parent_id = 0;
	enemy->split_count = 0;
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
			enemy.size = CP_Random_RangeFloat(ASTEROIDS_ENEMY_SIZE_MIN, ASTEROIDS_ENEMY_SIZE_MAX);

			enemy.hp.max = enemy.size * ASTEROIDS_ENEMY_BASE_MAX_HP;
			enemy.hp.current = enemy.hp.max;

			enemy.rotate_rate = Asteroids_Enemy_Random_Rotation();
			enemy.collider.diameter = ASTEROIDS_ENEMY_BASE_DIAMETER * enemy.size;
			enemy.velocity = CP_Vector_Zero();

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
			enemy.rotate_rate = Asteroids_Enemy_Random_Rotation();
			enemy.size = CP_Random_RangeFloat(ASTEROIDS_ENEMY_SIZE_MIN, ASTEROIDS_ENEMY_SIZE_MAX);
			enemy.collider.diameter = ASTEROIDS_ENEMY_BASE_DIAMETER * enemy.size;
			enemy.hp.max = enemy.size * ASTEROIDS_ENEMY_BASE_MAX_HP;
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

void Asteroids_Enemy_Spawn_Set_Interval(float interval)
{
	spawn_interval = interval;
}

void Asteroids_Enemy_Spawn_Decrease_Interval(float amount)
{
	Asteroids_Enemy_Spawn_Set_Interval(spawn_interval - amount);
}

void Asteroids_Enemy_Spawn_Scale_Interval(DIFFICULTY difficulty)
{
	Asteroids_Enemy_Spawn_Set_Interval(spawn_interval / (float)difficulty);
}

void Asteroids_Enemy_Spawn_Timer(Enemy enemy_pool[], int count)
{
	float dt = CP_System_GetDt();
	spawn_timer -= dt;

	if (spawn_timer <= 0)
	{
		spawn_timer = spawn_interval;
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
		x = CP_Random_RangeFloat(-ASTEROIDS_ENEMY_SPAWN_OFFSET, win_width + ASTEROIDS_ENEMY_SPAWN_OFFSET);
		y = CP_Random_RangeFloat(-ASTEROIDS_ENEMY_SPAWN_OFFSET, win_height + ASTEROIDS_ENEMY_SPAWN_OFFSET);
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
			CP_Image_DrawAdvanced(enemy_sprite, enemy.pos.x, enemy.pos.y, enemy.size * enemy_width, enemy.size * enemy_height, 255, enemy.rotation);

			if (enemy.status.hit)
			{
				CP_Image_DrawAdvanced(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy.size * enemy_width, enemy.size * enemy_height, 255, enemy.rotation);
			}
		}
	}
}

void Asteroids_Enemy_Idle_Rotate(Enemy* enemy, float rotate_rate, float dt)
{
	enemy->rotation += rotate_rate * dt;
}

void Asteroids_Enemy_Collide(Enemy* enemy1, Enemy* enemy2, Enemy enemy_pool[], int enemy_count, Player player)
{
	if ((enemy1->parent_id != enemy2->parent_id) || (enemy1->parent_id == 0 && enemy2->parent_id == 0))
	{
		if ((enemy1->size - enemy2->size) > (enemy1->size * 0.3f))
			Asteroids_Enemy_Death(enemy2);
		else if ((enemy2->size - enemy1->size) > (enemy2->size * 0.3f))
			Asteroids_Enemy_Death(enemy1);
		else
		{
			Asteroids_Enemy_Split(enemy1, player, enemy_pool, enemy_count);
			Asteroids_Enemy_Death(enemy1);
			Asteroids_Enemy_Split(enemy2, player, enemy_pool, enemy_count);
			Asteroids_Enemy_Death(enemy2);
		}

	}
}


//LIU KE
void Asteroids_Enemy_Spawn_Child(Enemy enemy_pool[], int pool_count, Enemy parent, int count)
{
	for (int i = 0; i < pool_count; i++)
	{
		Enemy enemy = enemy_pool[i];
		if (!enemy.active)
		{
			enemy.active = 1;
			enemy.parent_id = parent.id;
			enemy.pos = parent.pos;
			enemy.speed = parent.speed * count;
			enemy.size = parent.size / count;
			enemy.collider.diameter = parent.collider.diameter / count;
			enemy.rotate_rate = Asteroids_Enemy_Random_Rotation();
			enemy.velocity = CP_Vector_Add(parent.velocity, CP_Vector_Set(CP_Random_RangeFloat(-100, 100), CP_Random_RangeFloat(-100, 100)));
			enemy.hp.max = enemy.size * ASTEROIDS_ENEMY_BASE_MAX_HP;
			enemy.hp.current = enemy.hp.max;
			enemy.split_count++;

			enemy_pool[i] = enemy;
			return;
		}
	}
}

float Asteroids_Enemy_Random_Rotation()
{
	return CP_Random_RangeFloat(ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MIN, ASTEROIDS_ENEMY_IDLE_ROTATE_RATE_MAX);
}