#include "powerups.h"

// Powerup types
#define BULLET_SPLIT 1 
#define RECOVER_HP 2 
#define INVULNERABILITY 3 
#define INCREASE_BPM 4 

// Powerup size
#define POWERUP_MIN_VALUE 1   
#define POWERUP_MAX_VALUE 5

// Maximum number of powerup
#define POWERUP_MAX_SIZE 10

// Floating powerups spawn controller
bool Floating_powerup_status;

// Powerup status;
extern bool powerup_lifespan = false;
extern bool invulnerable = false;
extern bool bullet_split = false;
extern bool BPM = false;

// Static variables
#define RECOVER_HP_VALUE 5.0

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
		powerup_pool[i].lifespan = 0.0f;
		powerup_pool[i].status = false;
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

if (invulnerable)
{
	Asteroids_Powerup_Player_Invulernability(player);
}

	//if (powerup_lifespan == true) old code
	//{
	//	//Asteroids_Powerup_Lifespan_Manager(); old code
	//}
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

int Asteroids_Generate_Random_Powerup(void) //Returns random powerup type
{
	int random_powerup = CP_Random_RangeInt(POWERUP_MIN_VALUE, POWERUP_MAX_VALUE);
	return random_powerup;
}

void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position) //Guarded by RNG fnc, initialize powerup if rng is beaten
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
			powerup_pool[i].lifespan = 10.0f;
			return;
		}
	}
}

void Asteroids_Floating_Powerup_Lifespan_Manager(void)	// tracks time life of powerup
{
	float CurrentElaspedTime = CP_System_GetDt();

	static float TotalElaspedTime = 0;
	TotalElaspedTime += CurrentElaspedTime;
	
	if (TotalElaspedTime >= 10.0f)
	{
		Asteroids_Floating_Powerup_Manager(); //Spawns powerup every 10s
		TotalElaspedTime = 0.0f;
	}
}

void Asteroids_Floating_Powerup_Manager(void)	// Initialize variables for floating stuff
{
	//kinda whack, why do i have this. maybe i i'll change dis
	for(int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (!powerup_pool[i].active)
		{
			powerup_pool[i].active = true;
			powerup_pool[i].type = Asteroids_Generate_Random_Powerup();
			powerup_pool[i].pos = Asteroids_Utility_Generate_Random_Pos();
			powerup_pool[i].movement_Vel.x = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].movement_Vel.y = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].rotation = 50.0f;
			powerup_pool[i].lifespan = 10.0f;
			return;
		}
	}
}

void Asteroids_Powerup_Player_Collision(Powerup powerup[], struct Player* player)
{
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (!powerup_pool[i].active) // if not active, continue
		{
			continue;
		}

		Powerup* P = &powerup[i]; //Use *p cuz typing powerup[i] is too long
		if (Asteroids_Collision_CheckCollision_Circle_Test(P->collider, P->pos, player->collider, player->pos))
		{
			
			P[i].active = false; // set active to false to stop drawing
			P[i].status = true; // set status to true to start powerup lifetime.

			Asteroids_Powerup_Lifespan_Manager(&P[i]); // call function to track time. set status to false after lifespan exhausts

			if (P[i].type == ASTEROIDS_POWERUP_FUEL_PICKUP)
			{
				Asteroids_Powerup_Interact_Fuel_Pickup(player);
			}

			if (P[i].type == INCREASE_BPM)
			{
				BPM = true;
		/*		powerup_lifespan = true;*/		// old code
			}
			if (P[i].type == INVULNERABILITY)
			{
				invulnerable = true;
				//powerup_lifespan = true;		// old code
			}
			if (P[i].type == BULLET_SPLIT)
			{
				bullet_split = true;
				//powerup_lifespan = true;
			}
			if (P[i].type == RECOVER_HP)	// old code
			{
				Asteroids_Pickup_Interact_Hp(player);
			}
		}
	}
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

int Asteroids_Powerup_RNG(void)
{
	int rng = CP_Random_RangeInt(1, 20);
	return rng;
}

void Asteroids_Powerup_Interact_Fuel_Pickup(Player* player)
{
	Asteroids_Player_Refuel(ASTEROIDS_PLAYER_FUEL_REFUEL_AMOUNT, player);
}


void Asteroids_Pickup_Interact_Hp(Player* player)
{
	player->hp.current += RECOVER_HP_VALUE;
}


