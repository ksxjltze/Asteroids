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

// ENTRY POINT
void Asteroids_Obstacles_Init(void);
void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count);

// SPAWNING FUNCTIONS
void Asteroids_Spawn_Blackhole(void);
void Asteroids_Spawn_GammaRay(void);
void Asteroids_Spawn_Warning(void);
void Asteroids_Obstacle_TimeInterval(void);

// DRAWING
void Asteroids_Draw_Obstacle(Obstacle* obstacle);
void Asteroids_Environment_Draw_Warning(void);

// Collision
void Asteroids_Obstacle_Check_Collision(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count);
void Asteroids_Obstacle_Check_LifeSpan(Obstacle* obstacle);
