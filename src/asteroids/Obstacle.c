#include "Obstacle.h"
Obstacle Blackhole;
Obstacle GammaRay;

#define GammaRaySize 10

static float warning_lifespan = 1.0f;
float current_lifespan = 1.0f;
float obstacle_interval;

CP_Image Warning;
void Asteroids_Obstacles_Init(void)
{
	GammaRay.Sprite = CP_Image_Load("./Assets/GammaRay.png");
	Blackhole.Sprite = CP_Image_Load("./Assets/Blackhole.png");
	Warning = CP_Image_Load("./Assets/lmao.png");

	Blackhole.active = false;
	GammaRay.active = false;
	obstacle_interval = ASTEROIDS_OBSTACLE_SPAWN_INTERVAL;

}
void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count)
{
	if (Blackhole.active == true)
	{
		Asteroids_Draw_Obstacle(&Blackhole);
		Asteroids_Obstacle_Check_Collision(enemy_pool, player, &Blackhole, enemy_count);
		Asteroids_Obstacle_Check_LifeSpan(&Blackhole);
	}
	if (CP_Input_KeyDown(KEY_O))
	{
		Asteroids_Environment_Warning();
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

	if (GammaRay.active)
	{
		Asteroids_Draw_Obstacle(&GammaRay);
		Asteroids_Obstacle_Check_LifeSpan(&GammaRay);

		for (int j = 0; j < 100; j++)
		{
			if(Asteroids_Collision_CheckCollision_AABB_Circle(GammaRay.Collider, GammaRay.pos, enemy_pool[j].collider, enemy_pool[j].pos))
				Asteroids_Enemy_Death(&enemy_pool[j]);
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
	GammaRay.width = (float)WIN_WIDTH / 2;
	GammaRay.height = 20;
	GammaRay.Collider.width = GammaRay.width; // AABB Collider 
	GammaRay.Collider.height = 20;
	GammaRay.pos.x = 0 + GammaRay.width / 2;
	GammaRay.pos.y = posY;
	GammaRay.lifespan = 5.0;
	GammaRay.active = true;
	GammaRay.interval = ASTEROIDS_OBSTACLE_SPAWN_INTERVAL;
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
	if (obstacle->lifespan < 0)
		obstacle->active = false;
}

void Asteroids_Environment_Warning(void)
{
	float dt = CP_System_GetDt();
	current_lifespan -= dt;
	
	CP_Image_Draw(Warning, (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2, (float)WIN_WIDTH, 50.0f, (int)(fabsf(current_lifespan) / warning_lifespan * 255)); //(int)(current_lifespan/warning_lifespan) * 
	if (current_lifespan < -warning_lifespan)
	{
		current_lifespan = warning_lifespan;
	}
}

void Asteroids_Obstacle_TimeInterval(void)
{
	float dt = CP_System_GetDt();
	obstacle_interval -= dt;

	int rng = CP_Random_GetInt(1, 2);

	if (obstacle_interval < 0)
	{
		if (rng == 1)
			Asteroids_Spawn_Blackhole();
		else
			Asteroids_Spawn_GammaRay();
	}
	obstacle_interval = ASTEROIDS_OBSTACLE_SPAWN_INTERVAL;
}