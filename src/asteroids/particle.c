#include "particle.h"
#include "game.h"

CP_Vector pos;
//Particle pool
Particle particle[10000];

//Struct to hold data for Explosion particles
struct Explosion
{
	CP_Image image[8];
	float w[8];
	float h[8];
	int image_count;
	float delay;

}explosion;

/// <summary>
/// Initialize Particles
/// </summary>
/// <param name="void"></param>
void particle_init(void)
{
	explosion.image[0] = CP_Image_Load("./Assets/Explosion/Image001.png");
	explosion.image[1] = CP_Image_Load("./Assets/Explosion/Image002.png");
	explosion.image[2] = CP_Image_Load("./Assets/Explosion/Image003.png");
	explosion.image[3] = CP_Image_Load("./Assets/Explosion/Image004.png");
			
	explosion.image[4] = CP_Image_Load("./Assets/Explosion/Image005.png");
	explosion.image[5] = CP_Image_Load("./Assets/Explosion/Image006.png");
	explosion.image[6] = CP_Image_Load("./Assets/Explosion/Image007.png");
	explosion.image[7] = CP_Image_Load("./Assets/Explosion/Image008.png");

	explosion.image_count = 7;
	for (int i = 0; i < explosion.image_count; i++)
	{
		explosion.w[i] = (float)CP_Image_GetWidth(explosion.image[i]) * 0.3f;
		explosion.h[i] = (float)CP_Image_GetHeight(explosion.image[i]) * 0.3f;
	}

	explosion.delay = 0.1f;

	for (int i = 0; i < sizeof(particle)/ sizeof(particle[0]); i++)
	{
		particle[i].posX = 0;
		particle[i].posY = 0;
		particle[i].velocity.x = 0;
		particle[i].velocity.y = 0;
		particle[i].enabled = 0;
		particle[i].lifetime = 0;
		particle[i].life = 0;
		particle[i].delay = explosion.delay;
		particle[i].key_frame = 0;
		particle[i].timer = particle[i].delay;
		particle[i].loop = false;
	}

}

void draw_particle()
{

	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		
		if (particle[i].enabled)
		{
			CP_Image_Draw(explosion.image[particle[i].key_frame], particle[i].posX, particle[i].posY, particle[i].size * explosion.w[particle[i].key_frame], particle[i].size * explosion.h[particle[i].key_frame], (int)(particle[i].lifetime/particle[i].life * 255.0f));

		}

	}
}

//Generate particle velocity and set lifetime.
void particle_velocity(CP_Vector position, int particles, float min_velocity, float max_velocity, float size)
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
			particle[i].enabled = 1;
			particle[i].posX = position.x;
			particle[i].posY = position.y;
			particle[i].velocity = velocity;
			particle[i].life = particle[i].delay * (explosion.image_count);
			particle[i].lifetime = particle[i].life;
			particle[i].size = size;
			--particles;
		}
	}
}

void spawn_particles(CP_Vector position, int particles, float min_velocity, float max_velocity, float size)
{
	particle_velocity(position, particles, min_velocity, max_velocity, size);
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
			particle[i].timer -= dt;

			if (particle[i].timer <= 0)
			{
				particle[i].timer = particle[i].delay;
				if (particle[i].key_frame >= (explosion.image_count - 1))
				{
					if (particle[i].loop)
						particle[i].key_frame = 0;
				}
				else
					particle[i].key_frame++;
			}

			if (particle[i].lifetime <= 0)
			{
				particle[i].posX = 0;
				particle[i].posY = 0;
				particle[i].velocity.x = 0;
				particle[i].velocity.y = 0;
				particle[i].enabled = 0;
				particle[i].lifetime = 0;
				particle[i].timer = 0;
				particle[i].key_frame = 0;
				//particle_despawning(&particle[i]);
			}
		}


		//CP_Vector_Add(particle, velocity);

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
	p->timer = 0;
	p->key_frame = 0;
}

