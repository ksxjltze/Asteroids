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

typedef struct Dot
{
	float lifespan;
	CP_Image image[10];
	CP_Vector dimensions;
	CP_Vector pos;
	CP_Vector velocity;
	bool enabled;
} dot;

void particle_init();
void explosion_init(void);
void smoke_init(void);

#define MaxDotParticleArrSize 100
#define DotsPerArr 10
void Asteroids_Particle_Dot_Init(void);
void Asteroids_Particle_Dot_Spawn(CP_Vector pos);
void Asteroids_Particle_Draw_Dot(void);
void Asteroids_Particle_Dot_Despawn(dot* dot_particle);

void spawn_explosion_anim(CP_Vector position, float size);
void spawn_smoke_trail_anim(CP_Vector position, float size);

void particle_update(void);
void draw_particle();

Particle* Spawn_Particle(CP_Vector position, int particles, float min_velocity, float max_velocity, float size, Sprite sprite, int type, bool loop);

void smoke_velocity(CP_Vector position, int particles, float min_velocity, float max_velocity, float size);

void particle_despawning(Particle* particle);

void smoke_update(CP_Vector rotation, CP_Vector playerPos);
