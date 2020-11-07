#include "player.h"
#include "constants.h"

struct Player Asteroids_Player_Init(float player_width, float player_height)
{
	
	struct Player player;
	strcpy_s(player.name, 10, "Asteroids");
	player.active = 1;
	player.pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	player.collider.diameter = (player_width + player_height) / 2;

	player.hp.max = PLAYER_MAX_HP;
	player.hp.current = player.hp.max;
	player.speed = (float) SPEED;

	player.engine.fuel.current = PLAYER_MAX_FUEL;
	player.engine.fuel.max = player.engine.fuel.current;

	player.engine.drain_rate = DRAIN_RATE;
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

	if (player->hp.current <= 0)
	{
		player->active = 0;
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

void Asteroids_Player_Calculate_Fuel(Player* player)
{
	//temp
	if (player->engine.fuel.current <= 0)
	{
		player->engine.fuel.current = 0.0f;
		player->speed = 1;
		//if(player->active)
		//	player->active = 0;

		return;
	}

	player->engine.fuel.current -= player->engine.drain_rate * CP_System_GetDt();

}

void Asteroids_Player_Debug(Player player)
{
	//Asteroids_Collision_Debug_AABB_Draw(player.collider, player.pos);
	Asteroids_Collision_Debug_Circle_Draw(player.collider, player.pos);
}
