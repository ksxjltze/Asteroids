//---------------------------------------------------------
// file:	obstacles.c
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the game environment obstacles.
//			Handles drawing, spawning and collision with enemies and player.
//			Also contains code particle effects for enemy and blackhole collision
//			
//			
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "obstacles.h"
#include "utility.h"
#include "audio_manager.h"
#include "final_boss.h"
#include "powerups.h"


dot dot_pool[MaxDotParticleArrSize];


static float current_lifespan = 0.5f;
static float warning_lifespan = 0.5f;
static float obstacle_interval;
static float warning_interval;

static float dot_particle_lifespan;

extern bool invulnerable;
static bool pause_obstacles;

void Asteroids_Obstacles_Init(void)
{
	GammaRay.Sprite = CP_Image_Load("./Assets/GammaRay.png");
	Blackhole.Sprite = CP_Image_Load("./Assets/Blackhole.png");
	Warning = CP_Image_Load("./Assets/lmao.png");

	Blackhole.active = false;
	GammaRay.active = false;

	obstacle_interval = ASTEROIDS_OBSTACLE_SPAWN_INTERVAL;
	warning_interval = ASTEROIDS_OBSTACLE_WARNING_INTERVAL;
	dot_particle_lifespan = 1.5f;

	Asteroids_Particle_Dot_Init();

	pause_obstacles = false;

}

void Asteroids_Obstacles_Draw()
{
	if (Blackhole.active)
		Asteroids_Draw_Obstacle(&Blackhole);
	else if (GammaRay.active)
		Asteroids_Draw_Obstacle(&GammaRay);
}

void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count)
{
	float dt = CP_System_GetDt();
	if (!pause_obstacles)
	{
		Asteroids_Obstacle_TimeInterval();

		if (Blackhole.active == true)
		{
			Blackhole.pos = CP_Vector_Add(Blackhole.pos, CP_Vector_Scale(Blackhole.velocity, dt));
			Asteroids_Check_Collision_Blackhole_Enemy_Player(enemy_pool, player, &Blackhole, enemy_count);
		}

		if (GammaRay.active)
		{
			GammaRay.pos = CP_Vector_Add(GammaRay.pos, CP_Vector_Scale(GammaRay.velocity, dt));
			Asteroids_Check_Collision_Gammaray_Enemy_Player(enemy_pool, player, &GammaRay, enemy_count);

			for (int j = 0; j < 100; j++)
			{
				if (Asteroids_Collision_CheckCollision_AABB_Circle(GammaRay.Collider, GammaRay.pos, enemy_pool[j].collider, enemy_pool[j].pos))
					Asteroids_Enemy_Death(&enemy_pool[j]);
			}

		}
	}
}

void Asteroids_Obstacle_Spawn_Blackhole(void)
{
	Blackhole.width = ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH;
	Blackhole.height = ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH;
	Blackhole.speed = ASTEROIDS_OBSTACLE_BLACKHOLE_SPEED; //speed
	Blackhole.Collider2.diameter = Blackhole.width; //Circle collider
	Blackhole.pos.x = 0 - Blackhole.width / 2;

	CP_Vector direction = CP_Vector_Zero();
	direction.x = (float)WIN_WIDTH;
	direction.y = Blackhole.pos.y;
	Blackhole.velocity = CP_Vector_Subtract(direction, Blackhole.pos);
	Blackhole.velocity = CP_Vector_Normalize(Blackhole.velocity);
	Blackhole.velocity = CP_Vector_Scale(Blackhole.velocity, Blackhole.speed);
	
	Blackhole.active = true;
}


void Asteroids_Obstacle_Spawn_GammaRay(void)
{
	GammaRay.width = (float)(WIN_WIDTH / 4);
	GammaRay.height = ASTEROIDS_OBSTACLE_GAMARAY_HEIGHT;
	
	// AABB Collider 
	GammaRay.Collider.width = GammaRay.width; 
	GammaRay.Collider.height = GammaRay.height;
	
	GammaRay.pos.x = 0 - GammaRay.width / 2;

	GammaRay.speed = ASTEROIDS_OBSTACLE_GAMMARAY_SPEED;

	CP_Vector direction = CP_Vector_Zero();
	direction.x = (float)WIN_WIDTH;
	direction.y = GammaRay.pos.y;
	GammaRay.velocity = CP_Vector_Subtract(direction, GammaRay.pos);
	GammaRay.velocity = CP_Vector_Normalize(GammaRay.velocity);
	GammaRay.velocity = CP_Vector_Scale(GammaRay.velocity, GammaRay.speed);
	
	GammaRay.active = true;
}

void Asteroids_Draw_Obstacle(Obstacle* obstacle)
{
	CP_Image_DrawAdvanced(obstacle->Sprite, obstacle->pos.x, obstacle->pos.y, 
		obstacle->width, obstacle->height, 225, 0);

	if (obstacle->pos.x > WIN_WIDTH + obstacle->width || obstacle->pos.x + obstacle->width < 0  ||
		obstacle->pos.y > WIN_HEIGHT +obstacle->height|| obstacle->pos.y +obstacle->height < 0)
	{
		obstacle->active = false;
	}
}

void Asteroids_Check_Collision_Blackhole_Enemy_Player(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count)
{
	if (player)
	{
		if (!invulnerable)
		{
			if (Asteroids_Collision_CheckCollision_Circle_Test(obstacle->Collider2, obstacle->pos, player->collider, player->pos))
			{
				player->hp.current -= ASTEROIDS_OBSTACLE_BACKHOLE_DAMAGE;
			}
		}
	}
	for (int i = 0; i < enemy_count; i++)
	{
		if (!enemy_pool[i].active)
			continue;

		if (Asteroids_Collision_CheckCollision_Circle_Test(obstacle->Collider2, obstacle->pos, enemy_pool[i].collider, enemy_pool[i].pos))
		{
			enemy_pool[i].active = false;
			Asteroids_Particle_Dot_Spawn(enemy_pool[i].pos);
		}
	}
}

void Asteroids_Environment_Draw_Warning(void)
{
	float dt = CP_System_GetDt();
	current_lifespan -= dt;

	CP_Image_Draw(Warning, (float)WIN_WIDTH / 2, GammaRay.pos.y, (float)WIN_WIDTH, 80.0f, (int)(fabsf(current_lifespan) / warning_lifespan * 255));
	if (current_lifespan < -warning_lifespan)
	{
		current_lifespan = warning_lifespan;
	}
}

void Asteroids_Obstacle_Spawn_Warning(void)
{
	float posY = CP_Random_RangeFloat(50, (float)WIN_HEIGHT - 50);
	GammaRay.pos.y = posY;
	Blackhole.pos.y = posY;
	Asteroids_Audio_dangersound_Play();
}
void Asteroids_Obstacle_TimeInterval(void)
{
	float dt = CP_System_GetDt();
	if(!game.end)
	{
		obstacle_interval -= dt;
		warning_interval -= dt;
	}

	int rng = CP_Random_RangeInt(0, 1);

	if (warning_interval < 0)
	{
		Asteroids_Obstacle_Spawn_Warning();
		warning_interval = ASTEROIDS_OBSTACLE_WARNING_INTERVAL;
	}

	if (obstacle_interval < 3)
	{
		Asteroids_Environment_Draw_Warning();
	}

	if (obstacle_interval < 0)
	{
		if (rng == 1)
			Asteroids_Obstacle_Spawn_Blackhole();
		else
			Asteroids_Obstacle_Spawn_GammaRay();
		obstacle_interval = ASTEROIDS_OBSTACLE_SPAWN_INTERVAL;
		warning_interval = ASTEROIDS_OBSTACLE_WARNING_INTERVAL;
	}
}

void Asteroids_Check_Collision_Gammaray_Enemy_Player(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count)
{
	if (player)
	{
		if (!invulnerable)
		{
			if (Asteroids_Collision_CheckCollision_AABB_Circle(obstacle->Collider, obstacle->pos, player->collider, player->pos))
			{
				spawn_explosion_anim(player->pos, 20.0f);
				obstacle->active = false;
				player->hp.current -= ASTEROIDS_OBSTACLE_GAMMARAY_DAMAGE;
			}
		}
	}
	for (int i = 0; i < enemy_count; i++)
	{
		if (Asteroids_Collision_CheckCollision_AABB_Circle(obstacle->Collider, obstacle->pos, enemy_pool[i].collider, enemy_pool[i].pos))
		{
			enemy_pool[i].active = false;
			Asteroids_Enemy_Death(&enemy_pool[i]);
		}
	}
}

void Asteroids_Particle_Dot_Init(void)
{
	CP_Image Dot_sprite = CP_Image_Load("./Assets/Dot.png");
	for (int i = 0; i < MaxDotParticleArrSize; i++)
	{
		for (int j = 0; j < DotsPerArr; j++)
		{
			dot_pool[i].image[j] = Dot_sprite;
			dot_pool[i].velocity[j].x = CP_Random_RangeFloat(-25, 25);
			dot_pool[i].velocity[j].y = CP_Random_RangeFloat(-25, 25);
		}
	}
	for (int i = 0; i < MaxDotParticleArrSize; i++)
	{
		dot_pool[i].dimensions.x = 20.0f;
		dot_pool[i].dimensions.y = 20.0f;
		dot_pool[i].current_lifespan = dot_particle_lifespan;
		dot_pool[i].enabled = false;
	}
}
void Asteroids_Particle_Dot_Spawn(CP_Vector position)
{
	for (int i = 0; i < MaxDotParticleArrSize; i++)
	{
		if (!dot_pool[i].enabled) // find an inactive array and populate it.
		{
			for (int j = 0; j < DotsPerArr; j++)
			{
				dot_pool[i].pos[j] = position;
			}
			dot_pool[i].enabled = true;
			return;
		}
	}
}
void Asteroids_Particle_Draw_Dot(void)
{
	float dt = CP_System_GetDt();

	for (int i = 0; i < MaxDotParticleArrSize; i++)
	{
		if (!dot_pool[i].enabled) // if the array isnt active, don't draw
			continue;

		dot_pool[i].current_lifespan -= dt;
		for (int j = 0; j < DotsPerArr; j++)
		{
			dot_pool[i].velocity[j] = CP_Vector_Normalize(dot_pool[i].velocity[j]);
			dot_pool[i].velocity[j] = CP_Vector_Scale(dot_pool[i].velocity[j], 50);
			dot_pool[i].pos[j] = CP_Vector_Add(dot_pool[i].pos[j], CP_Vector_Scale(dot_pool[i].velocity[j], dt));
			CP_Image_DrawAdvanced(dot_pool[i].image[j], dot_pool[i].pos[j].x, dot_pool[i].pos[j].y, dot_pool[i].dimensions.x, dot_pool[i].dimensions.y, (int)((dot_pool[i].current_lifespan / dot_particle_lifespan) * 255), 255);
		}
		if (dot_pool[i].current_lifespan < 0)
		{
			Asteroids_Particle_Dot_Despawn(&dot_pool[i]);
		}
	}
}
void Asteroids_Particle_Dot_Despawn(dot* dot_particle)
{
	dot_particle->enabled = false;
	dot_particle->current_lifespan = dot_particle_lifespan;
}


void Asteroids_Obstacle_Spawn_Tutorial(Obstacle* obstacle, const float speed, const float height, const float width, CP_Vector pos)
{
	obstacle->width = width;
	obstacle->height = height;

	obstacle->pos.x = pos.x;
	obstacle->pos.y = pos.y;

	obstacle->speed = speed;

	CP_Vector direction = CP_Vector_Zero();
	direction.x = (float)WIN_WIDTH;
	direction.y = obstacle->pos.y;

	obstacle->velocity = CP_Vector_Subtract(direction, obstacle->pos);
	obstacle->velocity = CP_Vector_Normalize(obstacle->velocity);
	obstacle->velocity = CP_Vector_Scale(obstacle->velocity, obstacle->speed);

	obstacle->active = true;
}

void Asteroids_Help_Update_Obstacle_Pos(Obstacle* Annoying, const float dt)
{
	Annoying->pos = CP_Vector_Add(Annoying->pos, CP_Vector_Scale(Annoying->velocity, dt));
}