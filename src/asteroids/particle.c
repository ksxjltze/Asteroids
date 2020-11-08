#include "particle.h"
#include "game.h"

CP_Vector pos;

Particle particle[10000];

typedef struct Explosion
{
	CP_Image image[8];
}Explosion;

int explosion_vfx;

void particle_init(void)
{
	particle[0].image = CP_Image_Load("./Assets/Explosion/Image001.png");
	particle[1].image = CP_Image_Load("./Assets/Explosion/Image002.png");
	particle[2].image = CP_Image_Load("./Assets/Explosion/Image003.png");
	particle[3].image = CP_Image_Load("./Assets/Explosion/Image004.png");

	particle[4].image = CP_Image_Load("./Assets/Explosion/Image005.png");
	particle[5].image = CP_Image_Load("./Assets/Explosion/Image006.png");
	particle[6].image = CP_Image_Load("./Assets/Explosion/Image007.png");
	particle[7].image = CP_Image_Load("./Assets/Explosion/Image008.png");



	for (int i = 0; i < sizeof(particle)/ sizeof(particle[0]); i++)
	{
		particle[i].posX = 0;
		particle[i].posY = 0;
		particle[i].velocity.x = 0;
		particle[i].velocity.y = 0;
		particle[i].enabled = 0;
		particle[i].lifetime = 0;
		particle[i].life = 0;
	}
}

void draw_particle()
{
	float w;
	float h;

	for (int i = 0; i < 8; i++)
	{
		w = (float)CP_Image_GetWidth(particle[i].image);
		h = (float)CP_Image_GetHeight(particle[i].image);
	}

	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled)
		{
			CP_Image_Draw(particle[i].image, particle[i].posX, particle[i].posY, w, h, (int)(particle[i].lifetime/particle[i].life * 255.0f));

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
			particle[i].life = 2.5f;
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
			if (particle[i].lifetime <= 0)
			{
				particle_despawning(&particle[i]);
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
}

