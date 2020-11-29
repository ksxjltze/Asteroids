#include "final_boss.h"
#include "constants.h"
#include "state.h"

Enemy final_boss;
State bossState;
CP_Image final_boss_sprite[2];
CP_Image final_boss_sprite_hurt[2];

static bool lap;
static bool state_change;
static int id;
static float state_change_rate;

typedef struct Context
{
	Player* player;
	Enemy* enemy_pool;
	int enemy_poolSize;
	Bullet* bullet_pool;
} Context;

enum BossState {NONE, DEATH, IDLE, ATTACK, DODGE, BULLET_HELL};

#define ENEMY_POOL_SIZE 200
#define ASTEROIDS_POOLSIZE_BULLETS 999

static float boss_width, boss_height;
static float fire_rate;
static int battleStarted;

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
	//fire_rate = ASTEROIDS_FINAL_BOSS_FIRE_RATE;

	bossState.id = ATTACK;
	bossState.name = "Attack";
	bossState.action = &Asteroids_Final_Boss_State_Attack;

	battleStarted = 0;
	lap = false;
	state_change = false;
	id = bossState.id;
	state_change_rate = ASTEROIDS_FINAL_BOSS_STATE_CHANGE_RATE;
}

void Asteroids_Final_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	if (!battleStarted)
		Asteroids_Final_Boss_Summon_Criteria_Check();

	if (final_boss.active)
	{
		Asteroids_Final_Boss_Hp_Draw(final_boss);
		Asteroids_Final_Boss_State_Update(player, enemy_pool, enemy_count, bullet_pool);
		Asteroids_Final_Boss_State_Change_Manager();
		Asteroids_Final_Boss_State_Manager();
		Asteroid_Enemy_Check_Status(&final_boss);
		for (int i = 0; i < ASTEROIDS_POOLSIZE_BULLETS; i++)
		{
			bullet_pool[i] = Asteroids_Collision_CheckCollision_EnemyBoss_Bullet(&final_boss, bullet_pool[i], player);
		}
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
	final_boss.speed = 0;
	final_boss.split_count = 0; // no split, game ends when boss DIES
	final_boss.collider.diameter = final_boss.size * boss_width;

	final_boss.sprite_type = CP_Random_RangeInt(1, 1); //lmao
	battleStarted = 1;

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
			AngularDisplacement = CP_Matrix_Rotate(-ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * (ASTEROIDS_FINAL_BOSS_PROJECT_NUM / 2) + ASTEROIDS_FINAL_BOSS_PROJECTILE_ANGLE * i);
			Enemy* Boss_Projectile = Asteroids_Enemy_Spawn(enemy_pool, ENEMY_POOL_SIZE, Final_Boss.pos);
			Boss_Projectile->parent_id = final_boss.id;
			Boss_Projectile->id = i;

			Boss_Projectile->velocity = CP_Vector_Subtract (player->pos, Boss_Projectile->pos);
			Boss_Projectile->velocity = CP_Vector_Normalize(Boss_Projectile->velocity);
			Boss_Projectile->velocity = CP_Vector_Scale(Boss_Projectile->velocity, ASTEROIDS_FINAL_BOSS_PROJECTILE_SPEED);
			Boss_Projectile->velocity = CP_Vector_MatrixMultiply(AngularDisplacement, Boss_Projectile->velocity);
		}
		fire_rate = Asteroids_Final_Boss_FireRate();
	}
}
void Asteroids_Final_Boss_Summon_Criteria_Check(void)
{
	if (Score.enemy_kill_score >= ASTEROIDS_FINAL_BOSS_SUMMON_CRITERIA)
		Asteroids_Enemy_Final_Boss_Spawn();
}

void Asteroids_Final_Boss_State_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	Context context;
	context.player = player;
	context.enemy_pool = enemy_pool;
	context.enemy_poolSize = enemy_count;
	context.bullet_pool = bullet_pool;

	Asteroids_Final_Boss_State_CheckConditions();
	if (bossState.action)
		bossState.action(&context);
}

void Asteroids_Final_Boss_State_CheckConditions()
{
	//if (final_boss.hp.current <= 0)
	//{
	//	bossState.action = &Asteroids_Final_Boss_State_Death;
	//	bossState.name = "Death";
	//	bossState.id = DEATH;
	//}

	//if (CP_Input_KeyDown(KEY_E))
	//{
	//	bossState.action = &Asteroids_Final_Boss_State_Dodge;
	//	bossState.name = "Dodge";
	//	bossState.id = DODGE;
	//}
	//if (CP_Input_KeyDown(KEY_N))
	//{
	//	bossState.action = &Asteroids_Final_Boss_State_BulletHell;
	//	bossState.name = "BulletHell";
	//	bossState.id = BULLET_HELL;
	//}
	/*if (CP_Input_KeyDown(KEY_M))
	{
		bossState.id = IDLE;
		bossState.name = "Idle";
		bossState.action = &Asteroids_Final_Boss_State_Idle;
	}
	if (CP_Input_KeyDown(KEY_N))
	{
		bossState.id = ATTACK;
		bossState.name = "Attack";
		bossState.action = &Asteroids_Final_Boss_State_Attack;
	}*/
}

void Asteroids_Final_Boss_State_Idle(const void* context)
{
	Context parameters = *(Context*)context;
	Asteroids_Final_Boss_Shoot(final_boss, parameters.enemy_pool, parameters.player);
}

void Asteroids_Final_Boss_State_Death(const void* context)
{
	Asteroid_Final_Boss_Reset();
}

void Asteroid_Final_Boss_Reset()
{
	final_boss.active = 0;
	final_boss.hp.max = 0;
	final_boss.hp.current = 0;
	final_boss.speed = 0;
	final_boss.pos = CP_Vector_Zero();
	final_boss.size = 0;
	final_boss.split_count = 0;
	final_boss.collider.diameter = 0;
	final_boss.sprite_type = 0;
	bossState.id = NONE;
	bossState.name = "NONE";
	bossState.action = NULL;
}

void Asteroids_Final_Boss_State_Attack(const void* context)
{
	Context parameters = *(Context*)context;		
	Asteroids_Final_Boss_Shoot(final_boss, parameters.enemy_pool, parameters.player);
}

void Asteroids_Final_Boss_State_Dodge(void*context)
{
	Context parameters = *(Context*)context;
	Asteroids_Final_Boss_Shoot(final_boss, parameters.enemy_pool, parameters.player);
	Asteroids_Final_Boss_Dodge(&final_boss, parameters.player);

}
void Asteroids_Final_Boss_Dodge(Enemy* Final_boss, Player* player)
{
	float dt = CP_System_GetDt();
	Final_boss->speed = 1000.0f;
	CP_Vector max = CP_Vector_Zero();
	CP_Vector min = CP_Vector_Zero();
	max.y = (float)WIN_HEIGHT;
		
	Final_boss->velocity = CP_Vector_Subtract(max, min);
	Final_boss->velocity = CP_Vector_Normalize(Final_boss->velocity);
	Final_boss->velocity = CP_Vector_Scale(Final_boss->velocity, Final_boss->speed * dt);
	Final_boss->velocity.x = 0;

	if (Final_boss->pos.y + Final_boss->collider.diameter / 2 >= (float)WIN_HEIGHT)
		lap = true;
	if (Final_boss->pos.y - Final_boss->collider.diameter / 2 <= 0)
		lap = false;

	if (lap)
		Final_boss->pos = CP_Vector_Subtract(Final_boss->pos, Final_boss->velocity);

	if (!lap)
		Final_boss->pos = CP_Vector_Add(Final_boss->pos, Final_boss->velocity);
}
void Asteroids_Final_Boss_State_BulletHell(const void* context)
{
	Context parameters = *(Context*)context;
	Asteroids_Final_Boss_Shoot(final_boss, parameters.enemy_pool, parameters.player);
}
float Asteroids_Final_Boss_FireRate(void)
{
	switch (bossState.id)
	{
	case ATTACK:
		return ASTEROIDS_FINAL_BOSS_FIRE_RATE;
	case DODGE:
		return ASTEROIDS_FINAL_BOSS_DODGE_STATE_FIRE_RATE;
	case BULLET_HELL:
		return ASTEROIDS_FINAL_BOSS_BULLETHELL_STATE_FIRE_RATE;
	case IDLE:
		return ASTEROIDS_FINAL_BOSS_IDLE_STATE_FIRE_RATE;
	default:
		return 0;
	}
}
void Asteroids_Final_Boss_State_Manager(void)
{
	if (state_change)
	{
		id = Asteroids_Final_Boss_Random_State(id);
		state_change = false;
	}
	printf("%d\n", id);
	switch (id)
	{
	//case 4:
	//	bossState.action = &Asteroids_Final_Boss_State_Death;
	//	bossState.name = "Death";
	//	bossState.id = DEATH;
	case 2:
		bossState.id = IDLE;
		bossState.name = "Idle";
		bossState.action = &Asteroids_Final_Boss_State_Idle;
		break;
	case 3:
		bossState.id = ATTACK;
		bossState.name = "Attack";
		bossState.action = &Asteroids_Final_Boss_State_Attack;
		break;
	case 4:
		bossState.action = &Asteroids_Final_Boss_State_Dodge;
		bossState.name = "Dodge";
		bossState.id = DODGE;
		break;
	case 5:
		bossState.action = &Asteroids_Final_Boss_State_BulletHell;
		bossState.name = "BulletHell";
		bossState.id = BULLET_HELL;
		break;
	}
}

void Asteroids_Final_Boss_Idle(Enemy* Final_Boss, Player* player)
{
	Final_Boss->speed = 1;
}

int Asteroids_Final_Boss_Random_State(int old_id)
{
	int new_id = CP_Random_RangeInt(2, 5);

	while (new_id == old_id)
	{
		new_id = CP_Random_RangeInt(2, 5);
	}
	return new_id;
}
void Asteroids_Final_Boss_State_Change_Manager(void)
{
	float dt = CP_System_GetDt();
	state_change_rate -= dt;
	if (state_change_rate <= 0)
	{
		state_change = true;
		state_change_rate = ASTEROIDS_FINAL_BOSS_STATE_CHANGE_RATE;
	}
}

void Asteroids_Final_Boss_Hp_Draw(Enemy Final_Boss)
{
	CP_Vector mid = Asteroids_Utility_GetWindowMiddle();
	mid.x *= (float)0.33;
	mid.y *= 2;
	float scale = (float)(WIN_WIDTH * 2/3);
	float width = (Final_Boss.hp.current / Final_Boss.hp.max) * scale;
	float height = 30.0f;
	mid.y -= height;

	char boss_hp_buffer[16];
	sprintf_s(boss_hp_buffer, 16, ":%.0f/%.0f", Final_Boss.hp.current, Final_Boss.hp.max);
	CP_Settings_TextSize(height);
	CP_Settings_Fill(CP_Color_Create(244, 244, 244, 255));
	CP_Graphics_DrawRect(mid.x, mid.y, scale, height);
	CP_Settings_Fill(CP_Color_Create(255, 204, 229, 255));
	CP_Graphics_DrawRect(mid.x, mid.y, width, height);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
	CP_Font_DrawTextBox(boss_hp_buffer, (float)WIN_WIDTH / 2 - (WIN_WIDTH / 11), mid.y + (height / 2), 200);
}