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
	float lifespan;
}death_particle;


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
	Spawn_Particle_Static(player_pos, 1000, CP_Vector_Set(-100, -100), CP_Vector_Set(100, 100), 0.2f, death_particle.death_sprite, 10.0f);
}

//void player_death_init()
//{
//	for (int i = 0; i < deathParticles; i++)
//	{
//		death.sprite[i] = CP_Image_Load("./Assets/reddot.png");
//		death.position[i] = CP_Vector_Zero();
//		death.velocity[i].x = CP_Random_RangeFloat(-40, 40);
//		death.velocity[i].y = CP_Random_RangeFloat(-40, 40);
//	}
//	death.dimensions.x = (float)CP_Image_GetWidth(death.sprite[0]) * 0.5f;
//	death.dimensions.y = (float)CP_Image_GetHeight(death.sprite[0]) * 0.5f;
//	death.currentLifespan = 5;
//	death.maxLifespan = 5;
//	death.enabled = false;
//
//}


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

//void player_death_particle_velocity(CP_Vector position, int particles, float min_velocity,
//	float max_velocity, float size)
//{
//	CP_Vector velocity;
//	for (int i = 0; i < sizeof(death_particles) / sizeof(death_particles[0]); i++)
//	{
//		if (particles <= 0)
//			return;
//
//		if (death_particles[i].enabled == 0)
//		{
//			velocity.x = CP_Random_RangeFloat(min_velocity, max_velocity);
//			velocity.y = CP_Random_RangeFloat(min_velocity, max_velocity);
//			death_particles[i].enabled = 1;
//			death_particles[i].posX = position.x;
//			death_particles[i].posY = position.y;
//			death_particles[i].velocity = velocity;
//			death_particles[i].life = death_particles[i].sprite.duration;
//			death_particles[i].lifetime = death_particles[i].life;
//			//smoke_particle[i].lifetime = 999;
//			death_particles[i].size = size;
//			--particles;
//		}
//	}
//}

void smoke_velocity(CP_Vector position, int particles, float min_velocity, 
	float max_velocity, float size)
{
	CP_Vector velocity;
	for (int i = 0; i < sizeof(smoke_particle) / sizeof(smoke_particle[0]); i++)
	{
		if (particles <= 0)
			return;

		if (smoke_particle[i].enabled == 0)
		{
			velocity.x = CP_Random_RangeFloat(min_velocity, max_velocity);
			velocity.y = CP_Random_RangeFloat(min_velocity, max_velocity);
			smoke_particle[i].enabled = 1;
			smoke_particle[i].posX = position.x;
			smoke_particle[i].posY = position.y;
			smoke_particle[i].velocity = velocity;
			smoke_particle[i].life = smoke_particle[i].sprite.duration;
			smoke_particle[i].lifetime = smoke_particle[i].life;
			//smoke_particle[i].lifetime = 999;
			smoke_particle[i].size = size;
			--particles;
		}
	}
}

/*oid spawn_death_particles(CP_Vector position, int particles, float min_velocity,
	float max_velocity, float size)
{
	Spawn_Particle(position, particles, min_velocity, max_velocity, size, death.sprite, DEATH, false);
}*/

//void Asteroids_Particles_Spawn_Player_Death_Particles(CP_Vector pos)
//{
//	
//}

//void draw_player_death_anim(Player* player)
//{
//	//CP_Vector shit = Asteroids_Utility_GetWindowMiddle();
//	//CP_Image_Draw(death.sprite[0], shit.x, shit.y, 200, 200, 255);
//	if (death.enabled)
//	{
//		//printf("test\n");
//		float dt = CP_System_GetDt();
//		death.currentLifespan -= dt;
//		if (death.currentLifespan >= 0)
//		{
//			for (int i = 0; i < deathParticles; i++)
//			{
//				death.position[i] = player->pos;
//				death.velocity[i] = CP_Vector_Normalize(death.velocity[i]);
//				death.velocity[i] = CP_Vector_Scale(death.velocity[i], 300.0f * dt);
//				death.position[i] = CP_Vector_Add(death.position[i], death.velocity[i]);
//				CP_Image_Draw(death.sprite[i], death.position[i].x, death.position[i].y, death.dimensions.x, death.dimensions.y, 255); // (int)(death.currentLifespan/death.maxLifespan) *
//				//printf("%.2f %.2f\n", death.position[i].x, death.position[i].y);
//			}
//		}
//		if (death.currentLifespan <= 0)
//		{
//			player->active = 0;
//		}
//	}
//}

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
	//CP_Vector position = CP_Vector_Set(smoke_ptr->posX, smoke_ptr->posY);
	playerPos = CP_Vector_Subtract(playerPos, rotation);
	smoke_ptr->posX = playerPos.x;
	smoke_ptr->posY = playerPos.y;
}

void particle_despawning(Particle* p)
{
	p -> posX = 0;
	p->posY = 0;
	p->velocity.x = 0;
	p->velocity.y = 0;
	p->enabled = 0;
	p->lifetime = 0;
	p->sprite.time = 0;
	p->sprite.keyframe = 0;
}
