//---------------------------------------------------------
// file:	player.c
// author:	Lee Jia Keat
// contributors: Dania Mohd (Particle Effects and Animation)
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Player entity source file.
//			Contains functions for player functionality.
//			Defines the player entity struct.
//			Initializes, Draws and Updates a specified player entity.
//			Handles player movement and fuel management.
//			Provides an interface for damaging and disabling the player entity.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "player.h"
#include "constants.h"
#include <stdio.h>
#include "utility.h"
#include "game.h"
#include "upgrades.h"
#include "particle.h"
#include <math.h>
#include <time.h>

static Weapon Railgun_Base;
static Weapon Laser_Base;

struct Player Asteroids_Player_Init(float player_width, float player_height, bool is_apply_ugprades)
{
	struct Player player;
	strcpy_s(player.name, 10, "Asteroids");

	player.alpha = 255;

	player.active = 1;

	player.pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);
	player.velocity = CP_Vector_Zero();
	player.speed = (float) ASTEROIDS_PLAYER_BASE_MOVE_SPEED;

	player.collider.diameter = (player_width + player_height) / 2;

	player.hp.max = PLAYER_MAX_HP;
	player.hp.current = player.hp.max;

	player.engine.fuel.max = PLAYER_MAX_FUEL;
	player.engine.fuel.current = player.engine.fuel.max;
	player.engine.drain_rate = DRAIN_RATE;

	Railgun_Base.id = RAILGUN;
	Railgun_Base.damage = ASTEROIDS_WEAPON_RAILGUN_DAMAGE;
	Railgun_Base.fire_rate = ASTEROIDS_WEAPON_RAILGUN_FIRE_RATE;
	Railgun_Base.projectile_speed = ASTEROIDS_WEAPON_RAILGUN_PROJECTILE_SPEED;	
	Railgun_Base.isPiercing = false;

	player.weapon = Railgun_Base;
	player.weapon.projectile_count = 1;

	player.status.hit = 0;
	player.status.hit_cooldown = 0;

	player.rotation = 0;

	if (is_apply_ugprades)
		Asteroids_Upgrades_Apply_Upgrades(&player);
	spawn_smoke_trail_anim(player.pos, 0.3f);	//Dania
	return player;
}

void Asteroids_Player_Update(Player* player)
{
	Asteroids_Player_Calculate_Fuel(player);
	if (player->status.hit)
	{
		player->status.blink_cooldown -= CP_System_GetDt();
		player->status.hit_cooldown -= CP_System_GetDt();
		if (player->status.hit_cooldown <= 0)
		{
			player->status.hit = 0;
			player->status.hit_cooldown = PLAYER_HURT_WINDOW;
		}
		//DANIA START
		else if (player->status.blink_cooldown <= 0)
		{
			player->status.blink_cooldown = PLAYER_HURT_WINDOW / 6;
			if (player->alpha == 150)
			{
				player->alpha = 255;
			}
			else
			{
				player->alpha = 150;
			}
		}
	}
	else
	{
		player->alpha = 255;
	}
	//DANIA END
	Asteroids_Player_Update_Movement(player, CP_System_GetDt());

	if (player->hp.current <= 0)
	{
		Asteroids_Player_Death(player);
	}
}

void Asteroids_Player_Death(Player* player)
{
	//wait for timer then die.
	float time_left = 3;
	float dt = CP_System_GetDt();

	//unsigned int x_hours = 0;
	//unsigned int x_minutes = 0;
	//unsigned int x_seconds = 0;
	//unsigned int x_milliseconds = 0;
	//unsigned int count_down_time_in_secs = 0, time_left = 0;

	//clock_t x_startTime, x_countTime;
	//count_down_time_in_secs = 2;  // 1 minute is 60, 1 hour is 3600


	//x_startTime = clock();  // start clock
	//time_left = count_down_time_in_secs - x_seconds;   // update timer

	//while (time_left > 0)
	//{
	//	x_countTime = clock(); // update timer difference
	//	x_milliseconds = x_countTime - x_startTime;
	//	x_seconds = (x_milliseconds / (CLOCKS_PER_SEC)) - (x_minutes * 60);
	//	x_minutes = (x_milliseconds / (CLOCKS_PER_SEC)) / 60;
	//	x_hours = x_minutes / 60;


	//	time_left = count_down_time_in_secs - x_seconds; // subtract to get difference 


	//	printf("\nYou have %d seconds left ( %d )\n",time_left,count_down_time_in_secs);
	//}
	while (time_left > 0)
	{
		time_left -= dt;
	}

	if (time_left == 0)
	{
		//death particles.
		spawn_death_particles(player->pos, 30, 1, 10, 1);
		player->active = 0;
	}
}

void Asteroids_Player_Hit(Player* player, float damage) //Player hurt
{
	if (!player->status.hit)
	{
		player->hp.current -= damage;
		player->alpha = 150;
		player->status.hit = 1;
		//player->status.hit_cooldown = HURT_WINDOW;
		player->status.hit_cooldown = PLAYER_HURT_WINDOW;
		player->status.blink_cooldown = PLAYER_HURT_WINDOW/6;
	}
}

void Asteroids_Player_Draw(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, int alpha, float player_rotation)
{
	CP_Image_DrawAdvanced(player_sprite, pos.x, pos.y, player_width, player_height, alpha, player_rotation);
	
	float y = (float)sin(player_rotation);
	float x = (float)cos(player_rotation);

	if (player_rotation >= 0 && player_rotation <= 90)
	{
		pos.x -= y;
	}
	else if (player_rotation > 90 && player_rotation <= 180)
	{	
		pos.y -= player_height * x;
	}
	else if (player_rotation == -90)
	{
		pos.x += player_width;
	}
	else if (player_rotation == -180)
	{
		pos.y += player_width;
	}
}

void Asteroids_Player_Refuel(float amount, Player* player)
{
	float max = player->engine.fuel.max;
	player->engine.fuel.current += amount;

	if (player->engine.fuel.current > max)
		player->engine.fuel.current = max;

}

void Asteroids_Player_Drain_Fuel(Player* player)
{
	player->engine.fuel.current -= player->engine.drain_rate * CP_System_GetDt();
}

void Asteroids_Player_Calculate_Fuel(Player* player)
{
	//temp
	if (player->engine.fuel.current <= 0)
	{
		player->engine.fuel.current = 0.0f;
		player->speed = ASTEROIDS_PLAYER_SLOWED_SPEED;

		return;
	}

}

void Asteroids_Player_Simple_Movement(Player* player)
{
	CP_Vector oldPos = player->pos;
	bool isMoving = false;
	float speed = player->speed;
	float dt = CP_System_GetDt();

	if (player->engine.fuel.current <= 0)
		speed = ASTEROIDS_PLAYER_SLOWED_SPEED;

	if (CP_Input_KeyDown(KEY_W))
	{
		player->pos.y -= dt * speed;
		isMoving = true;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		player->pos.y += dt * speed;
		isMoving = true;
	}
	if (CP_Input_KeyDown(KEY_A))
	{
		player->pos.x -= dt * speed;
		isMoving = true;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		player->pos.x += dt * speed;
		isMoving = true;
	}

	if (player->engine.fuel.current > 0 && isMoving)
		player->engine.fuel.current -= player->engine.drain_rate * dt;

	if (!Asteroids_Utility_isInWindow(player->pos))
	{
		CP_Vector offset = CP_Vector_Subtract(oldPos, player->pos);
		player->pos = CP_Vector_Add(player->pos, offset);
	}
}

void Asteroids_Player_Check_Input(Player* player, float dt, CP_Vector direction)
{
	if (CP_Input_KeyDown(KEY_W))
	{
		Asteroids_Player_Accelerate(player, dt, direction);
	}
	else if (DIFFICULTY_OPTION < INSANE)
		Asteroids_Player_Decelerate(player, dt);

	if (CP_Input_KeyDown(KEY_S))
	{
		Asteroids_Player_Decelerate(player, dt);
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		Asteroids_Player_Strafe_Port(player, dt, direction);
	}

	if (CP_Input_KeyDown(KEY_D))
	{
		Asteroids_Player_Strafe_Starboard(player, dt, direction);
	}
}

void Asteroids_Player_Debug(Player player)
{
	//Asteroids_Collision_Debug_AABB_Draw(player.collider, player.pos);
	Asteroids_Collision_Debug_Circle_Draw(player.collider, player.pos);
}

void Asteroids_Player_Update_Movement(Player* player, float dt)
{
	CP_Vector movement = CP_Vector_Scale(player->velocity, dt);
	player->pos = CP_Vector_Add(player->pos, movement);
	

	if (!Asteroids_Utility_isInWindow(player->pos))
	{
		player->pos = CP_Vector_Add(player->pos, CP_Vector_Negate(movement));
		player->velocity = CP_Vector_Negate(movement);
	}
}

void Asteroids_Player_Accelerate(Player* player, float dt, CP_Vector direction)
{
	direction = CP_Vector_Normalize(direction);
	CP_Vector acceleration = CP_Vector_Scale(direction, dt);
	acceleration = CP_Vector_Scale(acceleration, player->speed);

	player->velocity = CP_Vector_Add(player->velocity, acceleration);
	Asteroids_Player_Drain_Fuel(player);
}

void Asteroids_Player_Decelerate(Player* player, float dt)
{
	CP_Vector deceleration = CP_Vector_Scale(player->velocity, -dt);
	player->velocity = CP_Vector_Add(player->velocity, deceleration);
	if (CP_Vector_Length(player->velocity) >= ASTEROIDS_PLAYER_FUEL_DRAIN_THRESHOLD && DIFFICULTY_OPTION >= INSANE)
		Asteroids_Player_Drain_Fuel(player);
}

void Asteroids_Player_Strafe_Port(Player* player, float dt, CP_Vector direction)
{
	CP_Vector strafe_vector = CP_Vector_Set(direction.y, -direction.x);
	Asteroids_Player_Accelerate(player, dt, strafe_vector);
}

void Asteroids_Player_Strafe_Starboard(Player* player, float dt, CP_Vector direction)
{
	CP_Vector strafe_vector = CP_Vector_Set(-direction.y, direction.x);
	Asteroids_Player_Accelerate(player, dt, strafe_vector);
}