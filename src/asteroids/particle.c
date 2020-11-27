#include "particle.h"
#include "game.h"
#include "constants.h"
#include "player.h"
#include <math.h>

CP_Vector pos;
//Particle pool
Particle particle[10000];
Particle smoke_particle[1];

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

/// <summary>
/// Initialize Particles
/// </summary>
/// <param name="void"></param>
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
	explosion.explosion_sprite = Asteroids_Sprite_Create(explosion.image, explosion.dimensions, explosion.image_count, explosion.delay * explosion.image_count, 0);
	
}

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
		particle[i].loop = false;
	}
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
	smoke.smoke_sprite = Asteroids_Sprite_Create(smoke.image, smoke.dimensions, smoke.image_count, smoke.delay * smoke.image_count, 0);
}

void draw_particle()
{
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled)
		{
			int keyframe = particle[i].sprite.keyframe;
			CP_Vector dimensions = particle[i].sprite.dimensions[keyframe];
			CP_Image_Draw(particle[i].sprite.images[keyframe], particle[i].posX, particle[i].posY, particle[i].size * dimensions.x, particle[i].size * dimensions.y, (int)(particle[i].lifetime / particle[i].life * 255.0f));

		}
	}
}


//Generate particle velocity and set lifetime.
void Spawn_Particle(CP_Vector position, int particles, float min_velocity,
	float max_velocity, float size, Sprite sprite, bool loop)
{
	CP_Vector velocity;
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particles <= 0)
			return;

		if (particle[i].enabled == 0)
		{
			velocity.x = CP_Random_RangeFloat(min_velocity, max_velocity);
			velocity.y = CP_Random_RangeFloat(min_velocity, max_velocity);
			particle[i].sprite = sprite;
			particle[i].enabled = 1;
			particle[i].posX = position.x;
			particle[i].posY = position.y;
			particle[i].velocity = velocity;
			particle[i].life = particle[i].sprite.duration;
			//particle[i].lifetime = particle[i].life;
			particle[i].lifetime = 999;
			particle[i].size = size;
			particle[i].loop = loop;
			--particles;
		}
	}
}

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
			//smoke_particle[i].lifetime = smoke_particle[i].life;
			smoke_particle[i].lifetime = 999;
			smoke_particle[i].size = size;
			--particles;
		}
	}
}

void spawn_explosion_anim(CP_Vector position, float size)
{
	int particles = 1;
	float min_velocity = 0;
	float max_velocity = 0;
	Spawn_Particle(position, particles, min_velocity, max_velocity, size, explosion.explosion_sprite, false);
}

void spawn_smoke_trail_anim(CP_Vector position, float size, CP_Vector rotation)
{
	int particles = 1;
	float min_velocity = 0;
	float max_velocity = 0;
	
	rotation = CP_Vector_Scale(rotation, 40);
	position = CP_Vector_Subtract(position, rotation);
	Spawn_Particle(position, particles, min_velocity, max_velocity, size, smoke.smoke_sprite, true);
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
			particle[i].lifetime -= dt;
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

