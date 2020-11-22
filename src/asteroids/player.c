#include "player.h"
#include "constants.h"
#include <stdio.h>
#include "utility.h"
#include "game.h"
#include "upgrades.h"

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

	player.engine.fuel.max = PLAYER_MAX_FUEL;
	player.engine.fuel.current = player.engine.fuel.max;
	player.engine.drain_rate = DRAIN_RATE;

	player.weapon.id = 0;
	player.weapon.damage = 0;
	player.weapon.fire_rate = 0;

	player.status.hit = 0;
	player.status.hit_cooldown = 0;

	Asteroids_Player_Apply_Upgrades(&player);

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

void Asteroids_Player_Apply_Upgrades(Player* player)
{
	Upgrade fuelCapacity = Asteroids_Upgrades_Get_Upgrade(FUEL_CAPACITY);
	Upgrade maxHealth = Asteroids_Upgrades_Get_Upgrade(MAX_HEALTH);
	Upgrade bulletDmg = Asteroids_Upgrades_Get_Upgrade(BULLET_DMG);
	
	if (fuelCapacity.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_FUEL_UPGRADE_AMOUNT * fuelCapacity.level;
		player->engine.fuel.max += upgrade;
		player->engine.fuel.current = player->engine.fuel.max;

		if (fuelCapacity.level > 0)
		{
			printf("Upgrade: Fuel Capacity increased by %f.\n", upgrade);
			printf("Fuel Capacity: %f\n", player->engine.fuel.max);
		}
	}

	if (maxHealth.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_AMOUNT * maxHealth.level;
		player->hp.max += upgrade;
		player->hp.current = player->hp.max;

		if (maxHealth.level > 0)
		{
			printf("Upgrade: Max Health increased by %f.\n", upgrade);
			printf("Max Health: %f\n", player->hp.max);
		}
	}

	if (bulletDmg.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_AMOUNT * bulletDmg.level;
		player->weapon.damage += upgrade;

		if (bulletDmg.level > 0)
		{
			printf("Upgrade: Bullet Damage increased by %f.\n", upgrade);
			printf("Bullet Damage: %f\n", player->weapon.damage);
		}
	}
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
	float speed = (float)ASTEROIDS_PLAYER_SIMPLE_SPEED;
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