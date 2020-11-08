#include "particle.h"
#include "game.h"

CP_Vector pos;

Particle particle[10000];

struct Explosion
{
	CP_Image image[8];
	float w[8];
	float h[8];
	int image_count;

}explosion;


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

	explosion.w[0] = (float)CP_Image_GetWidth(explosion.image[0]);
	explosion.w[1] = (float)CP_Image_GetWidth(explosion.image[1]);
	explosion.w[2] = (float)CP_Image_GetWidth(explosion.image[2]);
	explosion.w[3] = (float)CP_Image_GetWidth(explosion.image[3]);
	explosion.w[4] = (float)CP_Image_GetWidth(explosion.image[4]);
	explosion.w[5] = (float)CP_Image_GetWidth(explosion.image[5]);
	explosion.w[6] = (float)CP_Image_GetWidth(explosion.image[6]);
	explosion.w[7] = (float)CP_Image_GetWidth(explosion.image[7]);
											  
	explosion.h[0] = (float)CP_Image_GetHeight(explosion.image[0]);
	explosion.h[1] = (float)CP_Image_GetHeight(explosion.image[1]);
	explosion.h[2] = (float)CP_Image_GetHeight(explosion.image[2]);
	explosion.h[3] = (float)CP_Image_GetHeight(explosion.image[3]);

	explosion.h[4] = (float)CP_Image_GetHeight(explosion.image[4]);
	explosion.h[5] = (float)CP_Image_GetHeight(explosion.image[5]);
	explosion.h[6] = (float)CP_Image_GetHeight(explosion.image[6]);
	explosion.h[7] = (float)CP_Image_GetHeight(explosion.image[7]);

	explosion.image_count = 8;


	for (int i = 0; i < sizeof(particle)/ sizeof(particle[0]); i++)
	{
		particle[i].posX = 0;
		particle[i].posY = 0;
		particle[i].velocity.x = 0;
		particle[i].velocity.y = 0;
		particle[i].enabled = 0;
		particle[i].lifetime = 0;
		particle[i].life = 0;
		particle[i].delay = 0.1f;
		particle[i].key_frame = 0;
		particle[i].timer = particle[i].delay;
	}

}

void draw_particle()
{

	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		
		if (particle[i].enabled)
		{
			CP_Image_Draw(explosion.image[particle[i].key_frame], particle[i].posX, particle[i].posY, explosion.w[particle[i].key_frame], explosion.h[particle[i].key_frame], (int)(particle[i].lifetime/particle[i].life * 255.0f));

		}

	}
}

void particle_velocity(CP_Vector position, int particles, float min_velocity, float max_velocity)
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
			particle[i].life = particle[i].delay * (explosion.image_count - 1);
			particle[i].lifetime = particle[i].life;
			--particles;
		}
	}
}

void spawn_particles(CP_Vector position, int particles, float min_velocity, float max_velocity)
{
	particle_velocity(position, particles, min_velocity, max_velocity);
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
				particle[i].key_frame++;
				if (particle[i].key_frame >= 8)
				{
					particle[i].key_frame = 0;
				}
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

