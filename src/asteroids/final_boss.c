#include "final_boss.h"
#include "constants.h"
#include "state.h"

Enemy final_boss;
State bossState;
CP_Image final_boss_sprite[2];
CP_Image final_boss_sprite_hurt[2];

typedef struct Context
{
	Player* player;
	Enemy* enemy_pool;
	int enemy_poolSize;
	Bullet* bullet_pool;
} Context;

enum BossState {IDLE, ATTACK};

#define ENEMY_POOL_SIZE 200
#define ASTEROIDS_POOLSIZE_BULLETS 999

static float boss_width, boss_height;
static float fire_rate;

void Asteroids_Final_Boss_Init(void)

{
	final_boss_sprite[0] = CP_Image_Load("./Assets/final_boss.png");
	final_boss_sprite[1] = CP_Image_Load("./Assets/final_boss1.png");

	Asteroids_Utility_Generate_Hurt_Sprite(final_boss_sprite[0], &final_boss_sprite_hurt[0]);
	Asteroids_Utility_Generate_Hurt_Sprite(final_boss_sprite[1], &final_boss_sprite_hurt[1]);

	boss_width = ASTEROIDS_FINAL_BOSS_DIAMETER;
	boss_height = ASTEROIDS_FINAL_BOSS_DIAMETER;

	final_boss.active = 0;
	final_boss.id = ENEMY_POOL_SIZE + 1;
	fire_rate = ASTEROIDS_FINAL_BOSS_FIRE_RATE;

	bossState.id = ATTACK;
	bossState.name = "Attack";
	bossState.action = &Asteroids_Final_Boss_State_Attack;
}

void Asteroids_Final_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	Asteroids_Final_Boss_Summon_Criteria_Check();

	if (final_boss.active)
	{
		Asteroid_Enemy_Check_Status(&final_boss);
		Asteroids_Final_Boss_State_Update(player, enemy_pool, enemy_count, bullet_pool);
		Asteroids_Enemy_Check_Boss_Hp(&final_boss, *player, enemy_pool, final_boss.split_count);
		Asteroids_Final_Boss_Draw();
	}
	if (CP_Input_KeyTriggered(KEY_B))
	{
		Asteroids_Enemy_Final_Boss_Spawn();
		for (int i = 0; i < ENEMY_POOL_SIZE; i++)
		{
			if(enemy_pool[i].active)
				Asteroids_Enemy_Death(enemy_pool + i);
		}
	}
}

void Asteroids_Enemy_Final_Boss_Spawn(void)
{
	final_boss.hp.max = ASTEROIDS_FINAL_BOSS_MAX_HP;
	final_boss.hp.current = final_boss.hp.max;
	final_boss.speed = ASTEROIDS_FINAL_BOSS_MOVEMENT_SPEED;

	final_boss.pos = Asteroids_Utility_Generate_Random_Pos();

	final_boss.active = 1;
	final_boss.size = 10;
	final_boss.split_count = 0; // no split, game ends when boss DIES
	final_boss.collider.diameter = final_boss.size * boss_width;

	final_boss.sprite_type = CP_Random_RangeInt(0, 1);

	Asteroids_Enemy_Disable_Spawn(); // stop spawning of random asteroids
}
void Asteroids_Final_Boss_Draw(void)
{
	Asteroids_Enemy_Draw(&final_boss, 1, final_boss_sprite, final_boss_sprite_hurt, boss_width, boss_height);
}

void Asteroids_Final_Boss_Shoot(Enemy Final_Boss, Enemy enemy_pool[], Player* player)
{
	float dt = CP_System_GetDt();
	fire_rate -= dt;
	if (fire_rate <= 0)
	{
		CP_Matrix AngularDisplacement;
		for (int i = 0; i < ASTEROIDS_FINAL_BOSS_PROJECT_NUM; i++)
		{
			//(-ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * ASTEROIDS_FINAL_BOSS_PROJECT_NUM / 2) + ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * i)
			AngularDisplacement = CP_Matrix_Rotate(-ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * (ASTEROIDS_FINAL_BOSS_PROJECT_NUM / 2) + ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * i);
			//printf("Formula is %.2f\n", -ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * (ASTEROIDS_FINAL_BOSS_PROJECT_NUM / 2) + ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * i);
			//printf("Formula is %.2f\n", (-(ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * ASTEROIDS_FINAL_BOSS_PROJECT_NUM / 2) + ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * i));
			//printf("Hardcode is %.2f\n", -30 +  15.0f *i);
			Enemy* Boss_Projectile = Asteroids_Enemy_Spawn(enemy_pool, ENEMY_POOL_SIZE, Final_Boss.pos);
			Boss_Projectile->parent_id = final_boss.id;
			Boss_Projectile->id = i;

			Boss_Projectile->velocity = CP_Vector_Subtract (player->pos, Boss_Projectile->pos);
			Boss_Projectile->velocity = CP_Vector_Normalize(Boss_Projectile->velocity);
			Boss_Projectile->velocity = CP_Vector_Scale(Boss_Projectile->velocity, ASTEROIDS_FINAL_BOSS_PROJECTILE_SPEED);
			Boss_Projectile->velocity = CP_Vector_MatrixMultiply(AngularDisplacement, Boss_Projectile->velocity);
		}
		fire_rate = ASTEROIDS_FINAL_BOSS_FIRE_RATE;
	}
}
void Asteroids_Final_Boss_Summon_Criteria_Check(void)
{
	if (Score.enemy_kill_score >= ASTEROIDS_FINAL_BOSS_SUMMON_CRITERIA)
		Asteroids_Enemy_Final_Boss_Spawn();
}

void Asteroids_Final_Boss_State_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	Asteroids_Final_Boss_State_CheckConditions();
	Context context;
	context.player = player;
	context.enemy_pool = enemy_pool;
	context.enemy_poolSize = enemy_count;
	context.bullet_pool = bullet_pool;
	bossState.action(&context);
}

void Asteroids_Final_Boss_State_CheckConditions()
{
	return;
}

void Asteroids_Final_Boss_State_Idle(const void* context)
{

	
}

void Asteroids_Final_Boss_State_Attack(const void* context)
{
	Context parameters = *(Context*)context;		
	Asteroids_Final_Boss_Shoot(final_boss, parameters.enemy_pool, parameters.player);
	for (int i = 0; i < ASTEROIDS_POOLSIZE_BULLETS; i++)
	{
		parameters.bullet_pool[i] = Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(&final_boss, parameters.bullet_pool[i]);
	}
}

