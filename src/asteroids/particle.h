#pragma once
#include "game.h"
#include "collider_circle.h"


typedef struct Particles
{
	CP_Image image;
	CP_Vector velocity;
	float posX;
	float posY;
	int enabled;
	float lifetime;
	float life;

}Particle;

void particle_init(void);

void draw_particle(void);

void spawn_particles(CP_Vector position, int particles, float min_velocity, float max_velocity);

void particle_update(void);

void particle_velocity(CP_Vector position, int particles, float min_velocity, float max_velocity);

void particle_despawning(Particle* particle);
