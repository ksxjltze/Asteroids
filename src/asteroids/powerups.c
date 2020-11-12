#include "powerups.h"

#define BULLET_SPLIT 1 //looks = rotate 'W' by cw 90 degrees 
#define RECOVER_HP 2 // heart
#define INVULNERABILITY 3 // shield
#define INCREASE_BPM 4 // Bullets per minute 

#define POWERUP_MIN_VALUE 1   
#define POWERUP_MAX_VALUE 4 + 1

#define POWERUP_MAX_SIZE 10

bool Floating_powerup_status;
extern bool powerup_lifespan = false;
extern bool invulnerable = false;
extern bool bullet_split = false;
extern bool BPM = false;

//extern struct powerup
//{
//	bool powerup_lifespan;
//}

enum Asteroids_Powerup_Type { ASTEROIDS_POWERUP_FUEL_PICKUP = 5 };

CP_Image Powerup_Bulletsplit_Sprite;
CP_Image Powerup_Recover_Hp_Sprite;
CP_Image Powerup_Invulnerability_Sprite;
CP_Image Powerup_Increase_BPM_Sprite;

CP_Image Powerup_Fuel_Pickup_Sprite;


Powerup powerup_pool[POWERUP_MAX_SIZE];

Powerup Floating_Powerup;// OBJECT POOLING

static float width = 30.0f;
static float height = 30.0f;
static int powerup_count;

void Asteroids_Init_Powerups(void) //Initialize variables 
{
	powerup_count = 0;
	Floating_powerup_status = true;
	invulnerable = false;
	bullet_split = false;
	BPM = false;

	Powerup_Bulletsplit_Sprite = CP_Image_Load("./Assets/Powerup_Bullet_Split_Sprite.png");
	Powerup_Recover_Hp_Sprite = CP_Image_Load("./Assets/Powerup_RecoverHealth_Sprite.png");
	Powerup_Invulnerability_Sprite = CP_Image_Load("./Assets/Powerup_Invunerability_Sprite.png");
	Powerup_Increase_BPM_Sprite = CP_Image_Load("./Assets/Powerup_Shootfaster_Sprite.png");
	Powerup_Fuel_Pickup_Sprite = CP_Image_Load("./Assets/Powerup_Fuel_Pickup_Sprite.png");


	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		powerup_pool[i].pos = CP_Vector_Zero();
		powerup_pool[i].movement_Vel = CP_Vector_Zero();
		powerup_pool[i].active = false;
		powerup_pool[i].collider.diameter = width;
		powerup_pool[i].type = 0;
		powerup_pool[i].rotation = 0.0f;
	}
}

void Asteroids_Update_Powerups(struct Player* player) // draws and checks every frame
{	
	Asteroids_Floating_Powerup_Lifespan_Manager();
	
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		Powerup p = powerup_pool[i];
		if (p.active)
		{
			Asteroids_Powerup_Player_Collision(powerup_pool, *&player);
			Asteroids_Draw_Powerup(p.type, &powerup_pool[i].pos, p.movement_Vel, &powerup_pool[i].rotation);
			Asteroids_Draw_Powerup(Floating_Powerup.type, &Floating_Powerup.pos, Floating_Powerup.movement_Vel, &Floating_Powerup.rotation);
			Asteroids_Checkpowerup_Location();
		}
	}

	if (powerup_lifespan == true)
	{
		Asteroids_Powerup_Lifespan_Manager();
		if (invulnerable)
		{
			Asteroids_Powerup_Player_Invulernability(player);
		}
	}
}

void Asteroids_Draw_Powerup(int type, CP_Vector* pos, CP_Vector movement_vel, float* rotation)  // Draws specific powerup based on a random count
{

	switch (type) // change to delta time
	{
	case BULLET_SPLIT:
		CP_Image_DrawAdvanced(Powerup_Bulletsplit_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255, *rotation += 5.0f);
			break;

	case RECOVER_HP:
		CP_Image_DrawAdvanced(Powerup_Recover_Hp_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255, *rotation += 5.0f);
			break;

	case INVULNERABILITY:
		CP_Image_DrawAdvanced(Powerup_Invulnerability_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255, *rotation += 5.0f);
			break;

	case INCREASE_BPM:
		CP_Image_DrawAdvanced(Powerup_Increase_BPM_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255, *rotation += 5.0f);
			break;

	case ASTEROIDS_POWERUP_FUEL_PICKUP:
		CP_Image_DrawAdvanced(Powerup_Fuel_Pickup_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255, *rotation += 5.0f);
			break;

	default:;
	}
}

int Asteroids_Generate_Random_Powerup(void)
{
	int random_powerup = CP_Random_RangeInt(POWERUP_MIN_VALUE, POWERUP_MAX_VALUE);
	return random_powerup;
}

void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position) //Generates random movement
{
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (!powerup_pool[i].active)
		{
			powerup_pool[i].active = true;
			powerup_pool[i].type = Asteroids_Generate_Random_Powerup();
			powerup_pool[i].pos = position;
			powerup_pool[i].movement_Vel.x = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].movement_Vel.y = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].rotation = 50.0f;
			return;
		}
	}
}

void Asteroids_Floating_Powerup_Lifespan_Manager(void)	// tracks time life of powerup
{
	float CurrentElaspedTime = CP_System_GetDt();

	static float TotalElaspedTime = 0;
	TotalElaspedTime += CurrentElaspedTime;
	
	if (TotalElaspedTime >= 2.0f)
	{
		Asteroids_Floating_Powerup_Manager();
		TotalElaspedTime = 0.0f;
	}
}

void Asteroids_Floating_Powerup_Manager(void)	// function which resets powerup to different value after lifespend
{
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (!powerup_pool[i].active)
		{
			printf("Spawn\n");
			powerup_pool[i].active = true;
			powerup_pool[i].type = Asteroids_Generate_Random_Powerup();
			powerup_pool[i].pos = Asteroids_Utility_Generate_Random_Pos();
			powerup_pool[i].movement_Vel.x = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].movement_Vel.y = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].rotation = 50.0f;
			return;
		}
	}
}

void Asteroids_Powerup_Player_Collision(Powerup powerup[], struct Player* player)
{
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (!powerup_pool[i].active) // if 0, continue
		{
			continue;
		}
		Powerup* Powerup = &powerup[i];
		if (Asteroids_Collision_CheckCollision_Circle_Test(Powerup->collider, Powerup->pos, player->collider, player->pos))
		{
		
			powerup[i].active = false;
			printf("Collision test");

			if (powerup[i].type == ASTEROIDS_POWERUP_FUEL_PICKUP)
			{
				Asteroids_Powerup_Interact_Fuel_Pickup(player);
			}

			if (powerup[i].type == INCREASE_BPM)
			{
				BPM = true;
				powerup_lifespan = true;
			}
			if (powerup[i].type == INVULNERABILITY)
			{
				invulnerable = true;
				powerup_lifespan = true;
			}
			if (powerup[i].type == BULLET_SPLIT)
			{
				bullet_split = true;
				powerup_lifespan = true;
			}
		}
	}
}

void Asteroids_Powerup_Interact_Fuel_Pickup(Player* player)
{
	Asteroids_Player_Refuel(20, player);
}

int Asteroids_Powerup_RNG(void)
{
	int rng = CP_Random_RangeInt(1, 20);
	return rng;
}

void Asteroids_Checkpowerup_Location(void)
{
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (powerup_pool[i].active)
		{
			if (powerup_pool[i].pos.x > WIN_WIDTH || powerup_pool[i].pos.x < 0 ||
				powerup_pool[i].pos.y > WIN_HEIGHT || powerup_pool[i].pos.y < 0)
			{
				powerup_pool[i].active = false;
			}
		}
	}
}

