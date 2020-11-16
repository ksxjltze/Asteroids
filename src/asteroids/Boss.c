#include "Boss.h"

Enemy Boss;

CP_Image Boss_Sprite[2];
CP_Image Boss_HurtSprite[2];
float boss_width;
float boss_height;

#define Boss_Scale_Factor 17

void Asteroids_Boss_Init(CP_Image EnemySprite[], CP_Image EnemyHurtSprite[], float enemy_width, float enemy_height)
{
	Boss_Sprite[0] = EnemySprite[0];
	Boss_Sprite[1] = EnemySprite[1];
	Boss_HurtSprite[0] = EnemyHurtSprite[0];
	Boss_HurtSprite[1] = EnemyHurtSprite[1];

	boss_height = enemy_height;
	boss_width = enemy_width;
}

void Asteroids_Boss_Update(void)
{
	if (Boss.active)
	{
		Asteroids_Enemy_Draw_Boss();
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
	Boss.pos = Asteroids_Utility_Generate_Random_Pos();

	Boss.speed = 0.5f;
	Boss.size = Boss_Scale_Factor;

	Boss.hp.max = Boss.size * ASTEROIDS_ENEMY_BASE_MAX_HP;
	Boss.hp.current = Boss.hp.max;

	Boss.rotate_rate = Asteroids_Enemy_Random_Rotation();
	Boss.collider.diameter = ASTEROIDS_ENEMY_BASE_DIAMETER * Boss.size;
	Boss.velocity = CP_Vector_Zero();

	Boss.sprite_type = CP_Random_RangeInt(0, 1);
}