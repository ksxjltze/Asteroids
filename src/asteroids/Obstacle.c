#include "Obstacle.h"

Obstacle Blackhole;
Obstacle GammaRay[10];

#define GammaRaySize 10

void Asteroids_Obstacles_Init(void)
{
	Blackhole.Sprite = CP_Image_Load("./Assets/Blackhole.png");

	for (int i = 0; i < GammaRaySize; i++)
	{
		GammaRay[i].Sprite = CP_Image_Load("./Assets/GammaRay.png");
		GammaRay[i].active = false;
	}

	Blackhole.active = false;

}
void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count)
{
	if (Blackhole.active == true)
	{
		Asteroids_Draw_Obstacle(&Blackhole);
		Asteroids_Obstacle_Check_Collision(enemy_pool, player, &Blackhole, enemy_count);
		Asteroids_Obstacle_Check_LifeSpan(&Blackhole);
	}

	// GammaRay testing

	// Deactivate GammaRay
	if (CP_Input_KeyTriggered(KEY_H))
	{
		for (int i = 0; i < GammaRaySize; i++)
		{
			GammaRay[i].active = false;
		}
	}
	// Spawn GammaRay
	if (CP_Input_KeyTriggered(KEY_G))
	{
		Asteroids_Spawn_GammaRay();
	}
	for (int i = 0; i < GammaRaySize; i++)
	{
		if (GammaRay[i].active)
		{
			Asteroids_Draw_Obstacle(GammaRay + i);
			Asteroids_Obstacle_Check_LifeSpan(GammaRay+ i);
		}
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
	float posY = CP_Random_RangeFloat(50, (float)WIN_HEIGHT - 50);
	for (int i = 0; i < GammaRaySize; i++)
	{
		GammaRay[i].width = (float)WIN_WIDTH / 9;
		GammaRay[i].height = 20;
		GammaRay[i].Collider.width = 50; // AABB Collider 
		GammaRay[i].Collider.height = Blackhole.height;
		GammaRay[i].pos.x = GammaRay[i].width * i;
		GammaRay[i].pos.y = posY;
		GammaRay[i].lifespan = 5.0;
		GammaRay[i].active = true;
		//printf("GammaRay[%d].pos.x: %.2f\n", i, GammaRay[i].pos.x);
	}
}

void Asteroids_Draw_Obstacle(Obstacle* obstacle)
{
	CP_Image_DrawAdvanced(obstacle->Sprite, obstacle->pos.x, obstacle->pos.y, 
		obstacle->width, obstacle->height, 225, 0);
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
		}
	}
}

void Asteroids_Obstacle_Check_LifeSpan(Obstacle* obstacle)
{
	float dt = CP_System_GetDt();
	obstacle->lifespan -= dt;
	printf("obstacle lifespan is %.2f\n", obstacle->lifespan);
	if (obstacle->lifespan < 0)
		obstacle->active = false;
}