#pragma once
//---------------------------------------------------------
// file:	obstacles.h
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the game environment obstacles.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

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
	CP_Vector pos, velocity;
	struct Collider_AABB Collider;
	struct Collider_Circle Collider2;
	float width, height, speed;
	float interval;

	bool active;

}Obstacle;

typedef struct Dot
{
	float current_lifespan;
	int alpha;
	CP_Image image[10];
	CP_Vector dimensions;
	CP_Vector pos[10];
	CP_Vector velocity[10];
	bool enabled;
} dot;

Obstacle Blackhole;
Obstacle GammaRay;
CP_Image Warning;

/*				OBSTACLE MAIN ENTRY FUNCTIONS			*/
void Asteroids_Obstacles_Init(void);
void Asteroids_Obstacles_Update(Enemy enemy_pool[], Player* player, int enemy_count);


/*				OBSTACLE SPAWNING RELATED FUNCTIONS		*/
void Asteroids_Obstacle_Spawn_Blackhole(void);
void Asteroids_Obstacle_Spawn_GammaRay(void);
void Asteroids_Obstacle_Spawn_Warning(void);
void Asteroids_Obstacle_TimeInterval(void);


/*				OBSTACLE DRAWING RELATED FUNCTIONS		*/
void Asteroids_Draw_Obstacle(Obstacle* obstacle);
void Asteroids_Environment_Draw_Warning(void);


/*				OBTSACLE COLLISION RELATED FUNCTIONS	*/
void Asteroids_Check_Collision_Blackhole_Enemy_Player(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count);
void Asteroids_Check_Collision_Gammaray_Enemy_Player(Enemy enemy_pool[], Player* player, Obstacle* obstacle, int enemy_count);


/*				PARTICLE EFFECT FUNCTIONS				*/
#define MaxDotParticleArrSize 100
#define DotsPerArr 10
void Asteroids_Particle_Dot_Init(void);
void Asteroids_Particle_Dot_Spawn(CP_Vector pos);
void Asteroids_Particle_Draw_Dot(void);
void Asteroids_Particle_Dot_Despawn(dot* dot_particle);


/*				OBSTACLE FOR GUIDE SCREEN			*/
void Asteroids_Obstacle_Spawn_Tutorial(Obstacle* obstacle, const float speed, float height, float width, CP_Vector pos);
void Asteroids_Help_Update_Obstacle_Pos(Obstacle* Annoying, const float dt);