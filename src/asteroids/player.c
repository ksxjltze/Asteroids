#include "player.h"
#include "constants.h"
#include <stdio.h>

struct Player Asteroids_Player_Init(float player_width, float player_height)
{
	
	struct Player player;
	strcpy_s(player.name, 10, "Asteroids");

	player.active = 1;

	player.pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);
	player.velocity = CP_Vector_Zero();
	player.speed = (float) SPEED;

	player.collider.diameter = (player_width + player_height) / 2;

	player.hp.max = PLAYER_MAX_HP;
	player.hp.current = player.hp.max;

	player.engine.fuel.current = PLAYER_MAX_FUEL;
	player.engine.fuel.max = player.engine.fuel.current;
	player.engine.drain_rate = DRAIN_RATE;

	player.status.hit = 0;
	player.status.hit_cooldown = 0;

	return player;
}

void Asteroids_Player_Update(Player* player)
{
	Asteroids_Player_Calculate_Fuel(player);
	if (player->status.hit)
	{
		player->status.hit_cooldown -= CP_System_GetDt();
		if (player->status.hit_cooldown <= 0)
		{
			player->status.hit = 0;
			player->status.hit_cooldown = HURT_WINDOW;
		}
	}

	Asteroids_Player_Update_Movement(player, CP_System_GetDt());

	if (player->hp.current <= 0)
	{
		Asteroids_Player_Death(player);
	}

}

void Asteroids_Player_Death(Player* player)
{
	player->active = 0;
}

void Asteroids_Player_Hit(Player* player, float damage)
{
	if (!player->status.hit)
	{
		player->hp.current -= damage;
		player->status.hit = 1;
		player->status.hit_cooldown = HURT_WINDOW;
	}
}

void Asteroids_Player_Draw(CP_Image player_sprite, CP_Vector pos, float player_width, float player_height, float player_rotation)
{
	CP_Image_DrawAdvanced(player_sprite, pos.x, pos.y, player_width, player_height, 255, player_rotation);

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
		//if(player->active)
		//	player->active = 0;

		return;
	}

}



void Asteroids_Player_Simple_Movement(Player* player)
{
	if (CP_Input_KeyDown(KEY_W))
	{
		player->pos.y -= ASTEROIDS_PLAYER_SIMPLE_SPEED;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		player->pos.y += ASTEROIDS_PLAYER_SIMPLE_SPEED;
	}
	if (CP_Input_KeyDown(KEY_A))
	{
		player->pos.x -= ASTEROIDS_PLAYER_SIMPLE_SPEED;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		player->pos.x += ASTEROIDS_PLAYER_SIMPLE_SPEED;
	}
}

void Asteroids_Player_Check_Input(Player* player, float dt, CP_Vector direction)
{
	if (CP_Input_KeyDown(KEY_W))
	{
		Asteroids_Player_Accelerate(player, dt, direction);
	}

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
	if (CP_Vector_Length(player->velocity) >= 2.0f)
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