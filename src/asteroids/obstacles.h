#pragma once
#include "cprocessing.h"
#include "collider_aabb.h"
#include "collider_circle.h"
#include "collision_manager.h"
#include "utility.h"
#include "constants.h"
#include <stdio.h>
#include "player.h"
#include "enemy.h"
#include "particle.h"

typedef struct Obstacles
{
	CP_Image Sprite;
	CP_Vector pos, velocity; //suction;
	struct Collider_AABB Collider;
	struct Collider_Circle Collider2;
	float width, height, speed;
	float lifespan, interval;

	bool active;

}Obstacle;

typedef struct Dot
{
	float lifespan;
	int alpha;
	CP_Image image[10];
	CP_Vector dimensions;
	CP_Vector pos[10];
	CP_Vector velocity[10];
	bool enabled;
} dot;


// ENTRY POINT
void Asteroids_Obstacles_Init(void);
void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count);

// SPAWNING FUNCTIONS
void Asteroids_Obstacle_Spawn_Blackhole(void);
void Asteroids_Obstacle_Spawn_GammaRay(void);
void Asteroids_Obstacle_Spawn_Warning(void);
void Asteroids_Obstacle_TimeInterval(void);
void Asteroids_Obstacle_Check_LifeSpan(Obstacle* obstacle);

// DRAWING
void Asteroids_Draw_Obstacle(Obstacle* obstacle);
void Asteroids_Environment_Draw_Warning(void);

// Collision
void Asteroids_Check_Collision_Blackhole_Enemy_Player(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count);
void Asteroids_Check_Collision_Gammaray_Enemy_Player(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count);

// DEBUG
void Asteroids_Obstacles_Debug_BlackHole_To_Mouse();

#define MaxDotParticleArrSize 100
#define DotsPerArr 10
void Asteroids_Particle_Dot_Init(void);
void Asteroids_Particle_Dot_Spawn(CP_Vector pos);
void Asteroids_Particle_Draw_Dot(void);
void Asteroids_Particle_Dot_Despawn(dot* dot_particle);
void Asteroids_particle_dot_debug(void);