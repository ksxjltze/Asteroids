#include "particle.h"
#include "game.h"

CP_Image dot;
CP_Vector pos;

Particle particle[10000];



void particle_init(void)
{
	dot = CP_Image_Load("./Assets/Dot.png");
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
	float w = (float)CP_Image_GetWidth(dot) / 20;
	float h = (float)CP_Image_GetHeight(dot) / 20;
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particle[i].enabled)
		{
			CP_Image_Draw(dot, particle[i].posX, particle[i].posY, w, h, (int)(particle[i].lifetime/particle[i].life * 255.0f));

		}

	}
}

void spawn_particles(CP_Vector position, int particles)
{
	CP_Vector velocity;
	for (int i = 0; i < sizeof(particle) / sizeof(particle[0]); i++)
	{
		if (particles <= 0)
			return;

		if (particle[i].enabled == 0)
		{
			velocity.x = CP_Random_RangeFloat(-100, 100);
			velocity.y = CP_Random_RangeFloat(-100, 100);
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

void particle_velocity()
{
	

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

