#include "final_boss.h"

Enemy final_boss;
CP_Image final_boss_sprite, final_boss_sprite_hurt;

void Asteroids_Final_Boss_Init(void)

{
	final_boss_sprite = CP_Image_Load("./Assets/final_boss.png");
	final_boss.active = 0;

	Asteroids_Utility_Generate_Hurt_Sprite(final_boss_sprite, &final_boss_sprite_hurt);
}

void Asteroids_Final_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[])
{
	if (CP_Input_KeyTriggered(KEY_B))
	{
		Asteroids_Enemy_Final_Boss_Spawn();
	}
}
void Asteroids_Enemy_Final_Boss_Spawn(void)
{
	final_boss.hp.max = 100.0f;
	final_boss.hp.current = final_boss.hp.max;
	final_boss.pos = Asteroids_Utility_Generate_Random_Pos();
	final_boss.speed = 10.0f; //???
	//final_boss.velocity
	final_boss.active = 1;
	//final_boss.sprite_type = final_boss_sprite;
	final_boss.collider.diameter = 20.0f; // to decide diameter
}
