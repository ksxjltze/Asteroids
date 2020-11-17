#pragma once
#include "game.h"
#include "collider_circle.h"
#include <stdbool.h>
#include "sprite.h"

typedef struct Particles
{
	Sprite sprite;
	CP_Vector velocity;
	float posX;
	float posY;
	int enabled;
	float lifetime;
	float life;
	float size;
	bool loop;

}Particle;

void particle_init(void);

void draw_particle(void);

void spawn_particles(CP_Vector position, int particles, float min_velocity, float max_velocity, float size);

void particle_update(void);

void particle_velocity(CP_Vector position, int particles, float min_velocity, float max_velocity, float size);

void particle_despawning(Particle* particle);
