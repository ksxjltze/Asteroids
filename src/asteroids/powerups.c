#include "powerups.h"

#define BULLET_SPLIT 1 //looks = rotate 'W' by cw 90 degrees 
#define RECOVER_HP 2 // heart
#define INVULNERABILITY 3 // shield
#define INCREASE_BPM 4 // Bullets per minute 

#define POWERUP_MIN_VALUE 1 
#define POWERUP_MAX_VALUE 4

bool Floating_powerup_status;

Powerup Powerup_BulletSplit;
Powerup Powerup_Recover_Hp;
Powerup Powerup_Invulnerability;
Powerup Powerup_Increase_BPM;
Powerup Default;
Powerup Floating_Powerup;

void Asteroids_Init_Powerups(void) //Initialize variables 
{
	Default.height = 30.0f;
	Default.width = 30.0f;

	Floating_powerup_status = true;

	Powerup_BulletSplit.Sprite = CP_Image_Load("./Assets/Powerup_Bullet_Split_Sprite.png");
	Powerup_Recover_Hp.Sprite = CP_Image_Load("./Assets/Powerup_RecoverHealth_Sprite.png");
	Powerup_Invulnerability.Sprite = CP_Image_Load("./Assets/Powerup_Invunerability_Sprite.png");
	Powerup_Increase_BPM.Sprite = CP_Image_Load("./Assets/Powerup_Shootfaster_Sprite.png");

	Default.type = Asteroids_Generate_Random_Powerup();

	Asteroids_Floating_Powerup_Manager();
}

void Asteroids_Update_Powerups(void) // draws and checks every frame
{
	
	if (!Floating_powerup_status)
		Asteroids_Floating_Powerup_Manager();
	else
	{
		Asteroids_Floating_Powerup_Time_Manager();
		Asteroids_Draw_Powerup();
	}
}

void Asteroids_Draw_Powerup(void) // Draws specific powerup based on a random count
{
	if (Floating_powerup_status)
	{
		switch (Default.type)
		{
		case BULLET_SPLIT:
			CP_Image_Draw(Powerup_BulletSplit.Sprite, Default.pos.x += Default.Movement_Vel.x,
				Default.pos.y += Default.Movement_Vel.y, Default.width, Default.height, 255);
			if (Floating_powerup_status)
			{
				CP_Image_Draw(Powerup_BulletSplit.Sprite, Floating_Powerup.pos.x += Floating_Powerup.Movement_Vel.x,
					Floating_Powerup.pos.y += Floating_Powerup.Movement_Vel.y, Default.width, Default.height, 255);
			}break;

		case RECOVER_HP:
			CP_Image_Draw(Powerup_Recover_Hp.Sprite, Default.pos.x += Default.Movement_Vel.x,
				Default.pos.y += Default.Movement_Vel.y, Default.width, Default.height, 255);
			if (Floating_powerup_status)
			{
				CP_Image_Draw(Powerup_Recover_Hp.Sprite, Floating_Powerup.pos.x += Floating_Powerup.Movement_Vel.x,
					Floating_Powerup.pos.y += Floating_Powerup.Movement_Vel.y, Default.width, Default.height, 255);
			}break;

		case INVULNERABILITY:
			CP_Image_Draw(Powerup_Invulnerability.Sprite, Default.pos.x += Default.Movement_Vel.x,
				Default.pos.y += Default.Movement_Vel.y, Default.width, Default.height, 255);
			if (Floating_powerup_status)
			{
				CP_Image_Draw(Powerup_Invulnerability.Sprite, Floating_Powerup.pos.x += Floating_Powerup.Movement_Vel.x,
					Floating_Powerup.pos.y += Floating_Powerup.Movement_Vel.y, Default.width, Default.height, 255);
			}break;

		case INCREASE_BPM:
			CP_Image_Draw(Powerup_Increase_BPM.Sprite, Default.pos.x += Default.Movement_Vel.x,
				Default.pos.y += Default.Movement_Vel.y, Default.width, Default.height, 255);
			if (Floating_powerup_status)
			{
				CP_Image_Draw(Powerup_Increase_BPM.Sprite, Floating_Powerup.pos.x += Floating_Powerup.Movement_Vel.x,
					Floating_Powerup.pos.y += Floating_Powerup.Movement_Vel.y, Default.width, Default.height, 255);
			}break;

		default:;
		}
	}
}
int Asteroids_Generate_Random_Powerup(void)
{
	int random_powerup = CP_Random_RangeInt(POWERUP_MIN_VALUE, POWERUP_MAX_VALUE);
	return random_powerup;
}


void Asteroids_Generate_Powerup_On_Enemy_Death(CP_Vector position) //Generates random movement
{
	Default.type = Asteroids_Generate_Random_Powerup();
	Default.pos = position;
	Default.Movement_Vel = CP_Vector_Zero();
	Default.Movement_Vel.x = CP_Random_RangeFloat(-3, 3);
	Default.Movement_Vel.y = CP_Random_RangeFloat(-3, 3);
}


void Asteroids_Floating_Powerup_Time_Manager(void)	// tracks time life of powerup
{
	float CurrentElaspedTime = CP_System_GetDt();

	static float TotalElaspedTime = 0;

	TotalElaspedTime += CurrentElaspedTime;
	
	if (TotalElaspedTime >= 5.0f)
	{
		Floating_powerup_status = false;
		TotalElaspedTime = 0.0f;
	}
}
void Asteroids_Floating_Powerup_Manager(void)	// function which resets powerup to different value after lifespend
{
	Floating_Powerup.pos = Asteroids_Utility_Generate_Random_Pos();
	Floating_Powerup.type = Asteroids_Generate_Random_Powerup();
	Floating_Powerup.Movement_Vel = CP_Vector_Zero();
	Floating_Powerup.Movement_Vel.x = CP_Random_RangeFloat(-3, 3);
	Floating_Powerup.Movement_Vel.y = CP_Random_RangeFloat(-3, 3);
	Floating_powerup_status = true;
}
