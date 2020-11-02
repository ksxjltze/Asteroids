#pragma once
#include "game.h"

struct Dot {
	CP_Vector pos;
	struct Collider_Circle collider;
	CP_Vector velocity;
	int active;
};

typedef struct Particles
{
	CP_Vector velocity;
	float posX;
	float posY;
	int enabled;
	float lifetime;
	float life;

}Particle;

void particle_init(void);

void draw_particle(void);

void particle_velocity(void);

void particle_update(void);

void spawn_particles(CP_Vector position, int particles);

void particle_despawning(Particle* particle);
