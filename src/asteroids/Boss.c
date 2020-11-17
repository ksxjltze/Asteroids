#include "Boss.h"
#include "collider_circle.h"
#include "collision_manager.h"

Enemy Boss;

CP_Image Boss_Sprite[2];
CP_Image Boss_HurtSprite[2];
float boss_width;
float boss_height;

CP_Vector pos;

bool collide;

#define ASTEROIDS_POOLSIZE_BULLETS 999
#define Boss_Scale_Factor 17

void Asteroids_Boss_Init(CP_Image EnemySprite[], CP_Image EnemyHurtSprite[], float enemy_width, float enemy_height, Player* player)
{
	Boss.active = 0;
	Boss_Sprite[0] = EnemySprite[0];
	Boss_Sprite[1] = EnemySprite[1];
	Boss_HurtSprite[0] = EnemyHurtSprite[0];
	Boss_HurtSprite[1] = EnemyHurtSprite[1];

	boss_height = enemy_height;
	boss_width = enemy_width;

	pos = player->pos;
}

void Asteroids_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	float dt = CP_System_GetDt();
	if (Boss.active)
	{	
		Boss.pos = CP_Vector_Add(Boss.pos, CP_Vector_Scale(Boss.velocity, dt));
		Asteroids_Enemy_Draw_Boss();

		collide = Asteroids_Collision_CheckCollision_Circle(player->collider, player->pos, Boss.collider, Boss.pos);
		Asteroids_Collision_CheckCollision_Enemy_Enemy(enemy_pool, enemy_count, &Boss, *player);

		for (int i = 0; i < ASTEROIDS_POOLSIZE_BULLETS; i++)
		{
			//bullet_pool[i] = Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(Boss, bullet_pool[i]);
			Asteroid_Enemy_Check_Status(&Boss);
		}

		printf("hp is %.2f\n", Boss.hp.current);
		
		if (collide)
		{
			//player->hp.current = 0;
			//Boss.active = false;
		}
	}
	if (CP_Input_KeyTriggered(KEY_9))
	{
		Asteroids_Enemy_Boss_Spawn();
	}
}

void Asteroids_Enemy_Draw_Boss(void)
{
	Asteroids_Enemy_Draw(&Boss, 1, Boss_Sprite, Boss_HurtSprite, boss_width, boss_height);
}

void Asteroids_Enemy_Boss_Spawn(void)
{
	Boss.active = 1;
	Boss.pos = Asteroids_Boss_Random_Spawn_Location();

	Boss.speed = 20.0f;
	Boss.size = Boss_Scale_Factor;

	Boss.hp.max = 5 * ASTEROIDS_ENEMY_BASE_MAX_HP; //Boss.size *
	Boss.hp.current = Boss.hp.max;

	Boss.rotate_rate = Asteroids_Enemy_Random_Rotation();
	Boss.collider.diameter = ASTEROIDS_ENEMY_BASE_DIAMETER * Boss.size;
	Boss.velocity = pos;
	Boss.velocity = CP_Vector_Normalize(Boss.velocity);
	Boss.velocity = CP_Vector_Scale(Boss.velocity, Boss.speed);

	Boss.sprite_type = CP_Random_RangeInt(0, 1);
}
Bullet Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(Enemy enemy_pool, Bullet bullet)
{
	Enemy* enemy = &enemy_pool;

		if (Asteroids_Collision_CheckCollision_Circle(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
		{
			bullet.active = 0;
			bullet.pos = CP_Vector_Set(-1, -1);
			bullet.velocity = CP_Vector_Set(0, 0);

			Asteroids_Enemy_Hit(enemy, BULLET_DAMAGE);

			return bullet;
		}
	return bullet;
}

CP_Vector Asteroids_Boss_Random_Spawn_Location(void)
{
	CP_Vector position = CP_Vector_Zero();

	// Left side of screen
	float x1 = 0 - (float)ASTEROIDS_ENEMY_BASE_DIAMETER * Boss.size / 2;
	float y1 = (float)WIN_HEIGHT / 2;

	// Top side of screen
	float x2 = (float)WIN_WIDTH / 2;
	float y2 = 0 - (float)ASTEROIDS_ENEMY_BASE_DIAMETER * Boss.size / 2;

	// Bottom of screen?
	float x3 = x2;
	float y3 = (float)WIN_HEIGHT + ASTEROIDS_ENEMY_BASE_DIAMETER * Boss.size / 2;

	// Right side of screen
	float x4 = (float)WIN_WIDTH + ASTEROIDS_ENEMY_BASE_DIAMETER * Boss.size / 2;;
	float y4 = y2;

	int rng = CP_Random_RangeInt(1, 4);
	switch (rng)
	{
		case 1: 
			position.x = x1;
			position.y = y1;
			return position;
			break;
		case 2:
			position.x = x2;
			position.y = y2;
			return position;
			break;
		case 3:
			position.x = x3;
			position.y = y3;
			return position;
			break;
		case 4:
			position.x = x4;
			position.y = y4;
			return position;
			break;

		default:;
	}

	return position;
}