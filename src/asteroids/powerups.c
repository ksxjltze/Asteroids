#include "powerups.h"
#include "final_boss.h"
#include "audio_manager.h"

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

void Asteroids_Init_Powerups(void) //Initialize variables 
{
	Floating_powerup_status = true;
	invulnerable = false;
	bullet_split = false;
	BPM = false;

	Powerup_Bulletsplit_Sprite = CP_Image_Load("./Assets/Powerup_Bullet_Split_Sprite.png");
	Powerup_Recover_Hp_Sprite = CP_Image_Load("./Assets/Powerup_RecoverHealth_Sprite.png");
	Powerup_Invulnerability_Sprite = CP_Image_Load("./Assets/Powerup_Invunerability_Sprite.png");
	Powerup_Increase_BPM_Sprite = CP_Image_Load("./Assets/Powerup_Shootfaster_Sprite.png");
	Powerup_Fuel_Pickup_Sprite = CP_Image_Load("./Assets/Powerup_Fuel_Pickup_Sprite.png");


	for (int i = 0; i < POWERUP_MAX_SIZE; i++) //initialize to prevent getting rubbish values
	{
		powerup_pool[i].pos = CP_Vector_Zero();
		powerup_pool[i].movement_Vel = CP_Vector_Zero();
		powerup_pool[i].active = false;
		powerup_pool[i].collider.diameter = width;
		powerup_pool[i].type = 0;
		powerup_pool[i].rotation = 0.0f;
		powerup_pool[i].lifespan = 0.0f;
		powerup_pool[i].effect = false;
	}
}

void Asteroids_Update_Powerups(struct Player* player) // draws and checks every frame
{	
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		Powerup p = powerup_pool[i];

		if (powerup_pool[i].effect == true) // Update every frame if powerup effect is running
		{
			Asteroids_Powerup_Lifespan_Manager(&powerup_pool[i]);
		}
		if (powerup_pool[i].active == true) // Update every frame if power up is on screen
		{
			Asteroids_Checkpowerup_Location(&powerup_pool[i]);
			Asteroids_Powerup_Player_Collision(powerup_pool, *&player);
			Asteroids_Draw_Powerup(p.type, &powerup_pool[i].pos, p.movement_Vel, &powerup_pool[i].rotation);
			Asteroids_Draw_Powerup(Floating_Powerup.type, &Floating_Powerup.pos, Floating_Powerup.movement_Vel, &Floating_Powerup.rotation);
		}
	}
	Asteroids_Powerup_Player_Invulernability(player); //Draw invulnerability circle if invulnerable 

	Asteroids_Floating_Powerup_Lifespan_Manager(); // spawn random powerup every 10s
	if (CP_Input_KeyTriggered(KEY_F1)) //debug
	{
		player->hp.current = player->hp.max;
		invulnerable = true;
	}
}

void Asteroids_Draw_Powerup(int type, CP_Vector* pos, CP_Vector movement_vel, float* rotation)  // Draws specific powerup based on a random count
{
	switch (type) // Switch the powerup type to draw
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
		if (!powerup_pool[i].active && !powerup_pool[i].effect)
		{
			/*printf("spawn\n");*/
			powerup_pool[i].active = true;
			powerup_pool[i].type = Asteroids_Generate_Random_Powerup();
			powerup_pool[i].pos = position;
			powerup_pool[i].movement_Vel.x = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].movement_Vel.y = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].rotation = 50.0f;
			powerup_pool[i].lifespan = ASTEROIDS_POWERUP_LIFESPAN_DURATION;
			return;
		}
	}
}

void Asteroids_Floating_Powerup_Lifespan_Manager(void)	// tracks time life of powerup
{
	float CurrentElaspedTime = CP_System_GetDt();

	static float TotalElaspedTime = 0;
	if(!endgame.end)
		TotalElaspedTime += CurrentElaspedTime;

	if (TotalElaspedTime >= 10.0f)
	{
		Asteroids_Spawn_Floating_Powerup(); //Spawns powerup every 10s
		TotalElaspedTime = 0.0f;
	}
}

void Asteroids_Spawn_Floating_Powerup(void)	// Initialize variables for floating stuff
{
	//kinda whack, why do i have this. maybe i i'll change dis
	for(int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (!powerup_pool[i].active && !powerup_pool[i].effect) //if inactive and effect not running, spawn.
		{
			powerup_pool[i].active = true;
			powerup_pool[i].type = Asteroids_Generate_Random_Powerup();
			powerup_pool[i].pos = Asteroids_Utility_Generate_Random_Pos();
			powerup_pool[i].movement_Vel.x = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].movement_Vel.y = CP_Random_RangeFloat(-3, 3);
			powerup_pool[i].rotation = 50.0f;
			powerup_pool[i].lifespan = ASTEROIDS_POWERUP_LIFESPAN_DURATION;
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

		Powerup* P = &powerup[i];
		if (Asteroids_Collision_CheckCollision_Circle_Test(P->collider, P->pos, player->collider, player->pos))
		{
			powerup[i].effect = true; // effects starts running
			powerup[i].active = false; // set active to false to stop drawing
			if (powerup[i].type == ASTEROIDS_POWERUP_FUEL_PICKUP)
			{
				Asteroids_Powerup_Interact_Fuel_Pickup(player);
				Asteroids_Powerup_Reset(&powerup[i]);
			}
			else if (powerup[i].type == INCREASE_BPM)
			{
				BPM = true;
			}
			else if (powerup[i].type == INVULNERABILITY)
			{
				invulnerable = true;
			}
			else if (powerup[i].type == BULLET_SPLIT)
			{
				bullet_split = true;
			}
			else if (powerup[i].type == RECOVER_HP)
			{
				Asteroids_Pickup_Interact_Hp(player);
				Asteroids_Powerup_Reset(&powerup[i]);
			}
			Asteroids_Audio_PickUps_Play();
		}
	}
}
void Asteroids_Checkpowerup_Location(Powerup* powerup)
{
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (powerup->active && powerup->effect == false)
		{
			if (powerup->pos.x > WIN_WIDTH || powerup->pos.x < 0 || // If out of screen
				powerup->pos.y > WIN_HEIGHT || powerup->pos.y < 0)
			{
				Asteroids_Powerup_Reset(powerup); // Reset powerup
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
	player->hp.current += ASTEROIDS_POWERUP_HP_RECOVERY_VALUE;
}

void Asteroids_Powerup_Lifespan_Manager(Powerup* powerup)
{
	float dt = CP_System_GetDt();

	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		if (powerup_pool[i].type == powerup->type && powerup_pool[i].effect == powerup->effect) //same type, and both active
		{
			if (powerup_pool[i].lifespan > powerup->lifespan) // pool lifespan > pointer lifespan
			{
				powerup->lifespan = powerup_pool[i].lifespan; // write pool lifespan into pointer lifespan
				powerup_pool[i].effect = false;
			}
		}
	}
	powerup->lifespan -= dt;
	if (powerup->lifespan <= 0) //if lifespan reaches 0
	{
		powerup->effect = false; // set status to false, i.e: powerup effect stops
			switch (powerup->type)
			{
			case INVULNERABILITY:
				invulnerable = false;
				break;
			case BULLET_SPLIT:
				bullet_split = false;
				break;
			case INCREASE_BPM:
				BPM = false;
				break;
			default:;
								
		}
		Asteroids_Powerup_Reset(powerup); //reset the powerup
	}
}
void Asteroids_Powerup_Reset(Powerup* powerup)
{
	powerup->active = false;
	powerup->effect = false; // just to play safe
}