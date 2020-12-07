//---------------------------------------------------------
// file:	particle.c
// author:	Dania Mohd
// 
// contributors: Lee Jia Keat(death_particle), Bryan Koh Yan Wei(DeathP)
// email:	nuruldania.b@digipen.edu, l.jiakeat@digipen.edu, yanweibryan.koh@digipen.edu
//
// brief:	Simple particle system.
//			Handles initialization, spawning, updating and destroying of particles.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "particle.h"
#include "game.h"
#include "constants.h"
#include "player.h"
#include "utility.h"
#include <math.h>

CP_Vector pos;
//Particle pool
Particle particle[10000];
Particle smoke_particle[1];
Particle death_particles[10];
static float smoke_spawn_interval;
static Particle* smoke_ptr;

enum ParticleType {NONE, EXPLOSION, SMOKE, DEATH};

//Struct to hold data for Explosion particles
struct Explosion
{
	Sprite explosion_sprite;
	CP_Image image[8];
	CP_Vector dimensions[8];
	int image_count;
	float delay;

}explosion;

struct Smoke
{
	Sprite smoke_sprite;
	CP_Image image[3];
	CP_Vector dimensions[3];
	int image_count;
	float delay;
}smoke;

struct Death_Particle
{
	Sprite death_sprite;
	CP_Vector min_velocity;
	CP_Vector max_velocity;
	float min_size;
	float max_size;
	float current_lifespan;
}death_particle;

#define DVFXSize 200
typedef struct DeathP
{
	CP_Image sprite[DVFXSize];
	CP_Vector pos[DVFXSize];
	CP_Vector aceeleration[DVFXSize];
	CP_Vector dimension;
	float current_lifespan, max_lifespan;
	bool enabled;

}DeathP;

DeathP DP;
CP_Image DParticle;

/// <summary>
/// Initialize Particles
/// </summary>
/// <param name="void"></param>

void particle_init()
{
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		particle[i].posX = 0;
		particle[i].posY = 0;
		particle[i].velocity.x = 0;
		particle[i].velocity.y = 0;
		particle[i].enabled = 0;
		particle[i].lifetime = 0;
		particle[i].life = 0;
		particle[i].id = 0;
		particle[i].loop = false;
	}

	DParticle = CP_Image_Load("./Assets/reddot.png");
	DP.enabled = false;
}

void explosion_init(void)
{
	explosion.image[0] = CP_Image_Load("./Assets/Explosion/Image001.png");
	explosion.image[1] = CP_Image_Load("./Assets/Explosion/Image002.png");
	explosion.image[2] = CP_Image_Load("./Assets/Explosion/Image003.png");
	explosion.image[3] = CP_Image_Load("./Assets/Explosion/Image004.png");
			
	explosion.image[4] = CP_Image_Load("./Assets/Explosion/Image005.png");
	explosion.image[5] = CP_Image_Load("./Assets/Explosion/Image006.png");
	explosion.image[6] = CP_Image_Load("./Assets/Explosion/Image007.png");
	explosion.image[7] = CP_Image_Load("./Assets/Explosion/Image008.png");

	explosion.image_count = 8;
	for (int i = 0; i < explosion.image_count; i++)
	{
		explosion.dimensions[i].x = (float)CP_Image_GetWidth(explosion.image[i]) * ASTEROIDS_SPRITE_EXPLOSION_DIMENSIONS_SCALE_FACTOR;
		explosion.dimensions[i].y = (float)CP_Image_GetHeight(explosion.image[i]) * ASTEROIDS_SPRITE_EXPLOSION_DIMENSIONS_SCALE_FACTOR;
	}

	explosion.delay = 0.1f;
	explosion.explosion_sprite = Asteroids_Sprite_Create_Animated(explosion.image, explosion.dimensions, explosion.image_count, explosion.delay * explosion.image_count, 0);
	
}


void smoke_init()
{
	smoke.image[0] = CP_Image_Load("./Assets/SmokeTrail/smoke_0.png");
	smoke.image[1] = CP_Image_Load("./Assets/SmokeTrail/smoke_1.png");
	smoke.image[2] = CP_Image_Load("./Assets/SmokeTrail/smoke_2.png");

	smoke.image_count = 3;
	for (int i = 0; i < smoke.image_count; i++)
	{
		smoke.dimensions[i].x = (float)CP_Image_GetWidth(smoke.image[i]);
		smoke.dimensions[i].y = (float)CP_Image_GetHeight(smoke.image[i]);
	}

	smoke.delay = 0.1f;
	smoke.smoke_sprite = Asteroids_Sprite_Create_Animated(smoke.image, smoke.dimensions, smoke.image_count, smoke.delay * smoke.image_count, 0);
}

void Asteroids_Particles_Player_Death_Particle_Init()
{
	CP_Image image = CP_Image_Load("./Assets/reddot.png");
	float width = (float)CP_Image_GetWidth(image);
	float height = (float)CP_Image_GetHeight(image);
	death_particle.death_sprite = Asteroids_Sprite_Create_Static(image, CP_Vector_Set(width, height));
}

void Asteroids_Particle_Player_Death_Particle_Spawn(CP_Vector player_pos)
{
	Spawn_Particle_Static(player_pos, 100, CP_Vector_Set(-100, -100), CP_Vector_Set(100, 100), 0.2f, death_particle.death_sprite, 10.0f);
}

void draw_particle()
{
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled)
		{
			if (particle[i].animated)
			{
				int keyframe = particle[i].sprite.keyframe;
				CP_Vector dimensions = particle[i].sprite.dimensions[keyframe];
				CP_Image_Draw(particle[i].sprite.images[keyframe], particle[i].posX, particle[i].posY, particle[i].size * dimensions.x, particle[i].size * dimensions.y, (int)(particle[i].lifetime / particle[i].life * 255.0f));

			}
			else
			{
				CP_Image_Draw(particle[i].sprite.image, particle[i].posX, particle[i].posY, particle[i].size * particle[i].sprite.width, particle[i].size * particle[i].sprite.height, (int)(particle[i].lifetime / particle[i].life * 255.0f));
			}

		}
	}
}
//Generate particle velocity and set lifetime.
Particle* Spawn_Particle_Animated(CP_Vector position, int particles, float min_velocity,
	float max_velocity, float size, Sprite sprite, int type, bool loop)
{
	CP_Vector velocity;
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled == 0)
		{
			velocity.x = CP_Random_RangeFloat(min_velocity, max_velocity);
			velocity.y = CP_Random_RangeFloat(min_velocity, max_velocity);
			particle[i].sprite = sprite;
			particle[i].enabled = 1;
			particle[i].animated = true;
			particle[i].posX = position.x;
			particle[i].posY = position.y;
			particle[i].velocity = velocity;
			particle[i].life = particle[i].sprite.duration;
			particle[i].lifetime = particle[i].life;
			particle[i].size = size;
			particle[i].loop = loop;
			particle[i].id = type;
			return &particle[i];
		}
	}
	return NULL;
}

void Spawn_Particle_Static(CP_Vector position, int particle_count, CP_Vector min_velocity, CP_Vector max_velocity, float size, Sprite sprite, float life_span)
{
	CP_Vector velocity;
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled == 0)
		{
			if ((particle_count) <= 0)
				return;
			velocity.x = CP_Random_RangeFloat(min_velocity.x, max_velocity.x);
			velocity.y = CP_Random_RangeFloat(min_velocity.y, max_velocity.y);
			particle[i].size = size;
			particle[i].sprite = sprite;
			particle[i].enabled = 1;
			particle[i].animated = false;
			particle[i].posX = position.x;
			particle[i].posY = position.y;
			particle[i].velocity = velocity;
			particle[i].lifetime = life_span;
			particle[i].life = life_span;
			particle[i].id = DEATH;
			particle_count--;
		}
	}
}

void spawn_explosion_anim(CP_Vector position, float size)
{
	int particles = 1;
	float min_velocity = 0;
	float max_velocity = 0;
	Spawn_Particle_Animated(position, particles, min_velocity, max_velocity, size, explosion.explosion_sprite, EXPLOSION, false);
}

void spawn_smoke_trail_anim(CP_Vector position, float size)
{
	int particles = 1;
	float min_velocity = 0;
	float max_velocity = 0;

	smoke_ptr = Spawn_Particle_Animated(position, particles, min_velocity, max_velocity, size, smoke.smoke_sprite, SMOKE, true);
}

void particle_update()
{
	float dt = CP_System_GetDt();
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled)
		{
			particle[i].posX += particle[i].velocity.x * dt;
			particle[i].posY += particle[i].velocity.y * dt;

			if (particle[i].animated)
			{
				if (particle[i].loop == false)
				{
					particle[i].lifetime -= dt;
				}
				particle[i].sprite.time -= dt;

				if (particle[i].sprite.time <= 0)
				{
					particle[i].sprite.time = particle[i].sprite.duration / particle[i].sprite.frame_count;
					if (particle[i].sprite.keyframe >= (particle[i].sprite.frame_count - 1))
					{
						if (particle[i].loop)
							particle[i].sprite.keyframe = 0;
					}
					else
						particle[i].sprite.keyframe++;
				}

			}
			else
			{
				particle[i].lifetime -= dt;
			}

			if (particle[i].lifetime <= 0)
			{
				particle[i].posX = 0;
				particle[i].posY = 0;
				particle[i].velocity.x = 0;
				particle[i].velocity.y = 0;
				particle[i].enabled = 0;
				particle[i].lifetime = 0;
				particle[i].sprite.time = 0;
				particle[i].sprite.keyframe = 0;
			}
		}

	}
	draw_particle(); 

}

void smoke_update(CP_Vector rotation, CP_Vector playerPos)
{
	rotation = CP_Vector_Scale(rotation, 40);
	playerPos = CP_Vector_Subtract(playerPos, rotation);
	smoke_ptr->posX = playerPos.x;
	smoke_ptr->posY = playerPos.y;
}

void Asteroids_Player_Death_VFX_Spawn(Player* player)
{
	if (!DP.enabled)
	{
		for (int i = 0; i < DVFXSize; i++)
		{
			DP.sprite[i] = DParticle;
			DP.pos[i] = player->pos;
			DP.aceeleration[i] = CP_Vector_Set(CP_Random_RangeFloat(-250, 250), CP_Random_RangeFloat(-250, 250));
			DP.aceeleration[i] = CP_Vector_Normalize(DP.aceeleration[i]);
		}
		DP.current_lifespan = 5.0f;
		DP.max_lifespan = 5.0f;
		DP.dimension = CP_Vector_Set(25, 25);
		DP.enabled = true;
	}
}
void Asteroids_Player_Death_VFX_Update(Player* player)
{
	if (DP.enabled)
	{
		DP.current_lifespan -= CP_System_GetDt();
		if (DP.current_lifespan > 0)
		{
			for (int i = 0; i < DVFXSize; i++)
			{
				DP.pos[i] = CP_Vector_Add(DP.pos[i], CP_Vector_Scale(DP.aceeleration[i], CP_Random_RangeFloat(25, 250) * CP_System_GetDt()));
				CP_Image_Draw(DP.sprite[i], DP.pos[i].x, DP.pos[i].y, DP.dimension.x, DP.dimension.y, (int)(DP.current_lifespan / DP.max_lifespan * 255));
			}
		}
	}
	if (DP.current_lifespan < 0)
	{
		Asteroids_Player_Death_VFX_Despawn(player);
	}
}

void Asteroids_Player_Death_VFX_Despawn(Player* player)
{
	DP.enabled = false;
	player->active = 0;
}