#include "final_boss.h"
#include "constants.h"

Enemy final_boss;
CP_Image final_boss_sprite, final_boss_sprite_hurt;

#define ENEMY_POOL_SIZE 200
#define ASTEROIDS_POOLSIZE_BULLETS 999

float boss_width, boss_height;
float projectile_speed;

void Asteroids_Final_Boss_Init(void)

{
	final_boss_sprite = CP_Image_Load("./Assets/final_boss.png");
	final_boss.active = 0;

	Asteroids_Utility_Generate_Hurt_Sprite(final_boss_sprite, &final_boss_sprite_hurt);

	boss_width = 20.0f;
	boss_height = 20.0f;

	final_boss.id = ENEMY_POOL_SIZE + 1;
}

void Asteroids_Final_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	if (final_boss.active)
	{
		Asteroids_Final_Boss_Draw();
		Asteroid_Enemy_Check_Status(&final_boss);
		Asteroids_Enemy_Check_Boss_Hp(&final_boss, *player, enemy_pool, final_boss.split_count);
		for (int i = 0; i < ASTEROIDS_POOLSIZE_BULLETS; i++)
		{
			bullet_pool[i] = Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(&final_boss, bullet_pool[i]);
		}

	}
	if (CP_Input_KeyTriggered(KEY_B))
	{
		Asteroids_Enemy_Final_Boss_Spawn();
		for (int i = 0; i < ENEMY_POOL_SIZE; i++)
		{
			Asteroids_Enemy_Death(enemy_pool + i);
		}
	}
	if (CP_Input_KeyTriggered(KEY_N))
	{
		Asteroids_Final_Boss_Shoot(final_boss, enemy_pool, player);
	}
}
void Asteroids_Enemy_Final_Boss_Spawn(void)
{
	final_boss.hp.max = 100.0f;
	final_boss.hp.current = final_boss.hp.max;
	final_boss.pos = Asteroids_Utility_Generate_Random_Pos();
	final_boss.speed = 10.0f; //???

	final_boss.active = 1;
	final_boss.size = 10;
	final_boss.split_count = 0; // no split, game ends when boss DIES
	final_boss.collider.diameter = final_boss.size * boss_width; // to decide diameter

	projectile_speed = 200.0f;

	Asteroids_Enemy_Disable_Spawn(); // stop spawning of random asteroids
}
void Asteroids_Final_Boss_Draw(void)
{
	Asteroids_Enemy_Draw(&final_boss, 1, &final_boss_sprite, &final_boss_sprite_hurt, boss_width, boss_height);
}

void Asteroids_Final_Boss_Shoot(Enemy Final_Boss, Enemy enemy_pool[], Player* player)
{
	CP_Matrix AngularDisplacement;
	for (int i = 0; i < 5; i++)
	{
		AngularDisplacement = CP_Matrix_Rotate((float)(-30 + 15 * i));

		Enemy* Boss_Projectile = Asteroids_Enemy_Spawn(enemy_pool, ENEMY_POOL_SIZE, Final_Boss.pos);
		Boss_Projectile->parent_id = final_boss.id;
		Boss_Projectile->id = i;

		Boss_Projectile->velocity = CP_Vector_Subtract (player->pos, Boss_Projectile->pos);
		Boss_Projectile->velocity = CP_Vector_Normalize(Boss_Projectile->velocity);
		Boss_Projectile->velocity = CP_Vector_Scale(Boss_Projectile->velocity, projectile_speed);
		Boss_Projectile->velocity = CP_Vector_MatrixMultiply(AngularDisplacement, Boss_Projectile->velocity);
	}
}


