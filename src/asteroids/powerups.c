#include "powerups.h"

#define BULLET_SPLIT 1 //looks = rotate 'W' by cw 90 degrees 
#define RECOVER_HP 2 // heart
#define INVULNERABILITY 3 // shield
#define INCREASE_BPM 4 // Bullets per minute 

#define POWERUP_MIN_VALUE 1 
#define POWERUP_MAX_VALUE 4

#define POWERUP_MAX_SIZE 100

bool Floating_powerup_status;

CP_Image Powerup_Bulletsplit_Sprite;
CP_Image Powerup_Recover_Hp_Sprite;
CP_Image Powerup_Invulnerability_Sprite;
CP_Image Powerup_Increase_BPM_Sprite;

Powerup powerup_pool[POWERUP_MAX_SIZE];

Powerup Floating_Powerup;// OBJECT POOLING

static float width = 30.0f;
static float height = 30.0f;

void Asteroids_Init_Powerups(void) //Initialize variables 
{
	Floating_powerup_status = true;

	Powerup_Bulletsplit_Sprite = CP_Image_Load("./Assets/Powerup_Bullet_Split_Sprite.png");
	Powerup_Recover_Hp_Sprite = CP_Image_Load("./Assets/Powerup_RecoverHealth_Sprite.png");
	Powerup_Invulnerability_Sprite = CP_Image_Load("./Assets/Powerup_Invunerability_Sprite.png");
	Powerup_Increase_BPM_Sprite = CP_Image_Load("./Assets/Powerup_Shootfaster_Sprite.png");

	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		powerup_pool[i].pos = CP_Vector_Zero();
		powerup_pool[i].movement_Vel = CP_Vector_Zero();
		powerup_pool[i].active = false;
		powerup_pool[i].collider.width = width;
		powerup_pool[i].collider.height = height;
		powerup_pool[i].type = 0;
	}
}

void Asteroids_Update_Powerups(void) // draws and checks every frame
{
	Asteroids_Floating_Powerup_Lifespan_Manager();
	for (int i = 0; i < POWERUP_MAX_SIZE; i++)
	{
		Powerup p = powerup_pool[i];
		if (p.active)
		{
			Asteroids_Draw_Powerup(p.type, &powerup_pool[i].pos, p.movement_Vel);
		}
	}

	Asteroids_Draw_Powerup(Floating_Powerup.type, &Floating_Powerup.pos, Floating_Powerup.movement_Vel);

}
void Asteroids_Draw_Powerup(int type, CP_Vector* pos, CP_Vector movement_vel)  // Draws specific powerup based on a random count
{
	switch (type) // change to delta time
	{
	case BULLET_SPLIT:
		CP_Image_Draw(Powerup_Bulletsplit_Sprite, pos->x += movement_vel.x, 
			pos->y += movement_vel.y, width, height, 255);
			break;

	case RECOVER_HP:
		CP_Image_Draw(Powerup_Recover_Hp_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255);
			break;

	case INVULNERABILITY:
		CP_Image_Draw(Powerup_Invulnerability_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255);
			break;

	case INCREASE_BPM:
		CP_Image_Draw(Powerup_Increase_BPM_Sprite, pos->x += movement_vel.x,
			pos->y += movement_vel.y, width, height, 255);
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
			return;
		}
	}
}
