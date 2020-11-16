#include "Obstacle.h"

Obstacle Blackhole;
Obstacle GammaRay;

void Asteroids_Obstacles_Init(void)
{
	Blackhole.Sprite = CP_Image_Load("./Assets/Blackhole.png");
	GammaRay.Sprite = CP_Image_Load("./Assets/GammaRay.png");

	Blackhole.active = false;
	GammaRay.active = false;
}
void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count)
{
	if (Blackhole.active == true)
	{
		Asteroids_Draw_Obstacle(&Blackhole);
		Asteroids_Obstacle_Check_Collision(enemy_pool, player, &Blackhole, enemy_count);
	}
	if (GammaRay.active == true)
	{
		Asteroids_Draw_Obstacle(&GammaRay);
	}

	// GammaRay testing

	// Deactivate GammaRay
	if (CP_Input_KeyTriggered(KEY_H))
	{
		GammaRay.active = false;
	}
	// Spawn GammaRay
	if (CP_Input_KeyTriggered(KEY_G))
	{
		Asteroids_Spawn_GammaRay();
	}

	// Blackhole testing

	// Spawn Blackhole
	if (CP_Input_KeyTriggered(KEY_B))
	{
		Asteroids_Spawn_Blackhole();
	}

	// Deactivate Blackhole
	if (CP_Input_KeyTriggered(KEY_N))
	{
		Blackhole.active = false;
	}
}

void Asteroids_Spawn_Blackhole(void)
{
	Blackhole.width = 100;
	Blackhole.height = 100;
	Blackhole.Collider2.diameter = Blackhole.width; //Circle collider
	Blackhole.pos = Asteroids_Utility_Generate_Random_Pos();
	Blackhole.lifespan = 10.0;
	Blackhole.active = true;
}


void Asteroids_Spawn_GammaRay(void)
{
	GammaRay.width = (float)WIN_WIDTH;
	GammaRay.height = 50;
	GammaRay.Collider.width = Blackhole.width; // AABB Collider
	GammaRay.Collider.height = Blackhole.height;
	GammaRay.pos.x = (float)WIN_WIDTH / 2;
	GammaRay.pos.y = CP_Random_RangeFloat(GammaRay.height, (float)WIN_HEIGHT - GammaRay.height);
	GammaRay.lifespan = 10.0;
	GammaRay.active = true;
}

void Asteroids_Draw_Obstacle(Obstacle* obstacle)
{
	CP_Image_DrawAdvanced(obstacle->Sprite, obstacle->pos.x, obstacle->pos.y, 
		obstacle->width, obstacle->height, 150, 0);
}

void Asteroids_Obstacle_Check_Collision(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count)
{
	if (Asteroids_Collision_CheckCollision_Circle_Test(obstacle->Collider2, obstacle->pos, player->collider, player->pos))
	{
		player->hp.current -= ASTEROIDS_OBSTACLE_BACKHOLE_DAMAGE;
	}

	for (int i = 0; i < enemy_count; i++)
	{
		if (Asteroids_Collision_CheckCollision_Circle_Test(obstacle->Collider2, obstacle->pos, enemy_pool[i].collider, enemy_pool[i].pos))
		{
			enemy_pool[i].active = false;
			//spawn_particles(enemy_pool[i].pos, 8, 0, 0, enemy_pool[i].size);
		}
	}
}