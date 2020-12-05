#pragma once
#include "game.h"
#include "collider_circle.h"
#include <stdbool.h>
#include "sprite.h"
#include "enemy.h"

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
	int id;
	bool loop;

}Particle;

#define deathParticles 20

struct Death
{
	CP_Image sprite[deathParticles];
	CP_Vector dimensions;
	CP_Vector position[deathParticles];
	CP_Vector velocity[deathParticles];
	float currentLifespan;
	float maxLifespan;
	bool enabled;
} death;

void particle_init();
void explosion_init(void);
void smoke_init(void);
void player_death_init(void);

void draw_player_death_anim(Player* player);
void spawn_explosion_anim(CP_Vector position, float size);
void spawn_smoke_trail_anim(CP_Vector position, float size);
void spawn_death_particles(CP_Vector position, int particles, float min_velocity,
	float max_velocity, float size);

void particle_update(void);
void draw_particle();

Particle* Spawn_Particle_Animated(CP_Vector position, int particles, float min_velocity, float max_velocity, float size, Sprite sprite, int type, bool loop);

void smoke_velocity(CP_Vector position, int particles, float min_velocity, float max_velocity, float size);

void particle_despawning(Particle* particle);

void smoke_update(CP_Vector rotation, CP_Vector playerPos);
