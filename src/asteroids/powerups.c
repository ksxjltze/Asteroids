#include "powerups.h"

#define BULLET_SPLIT 1 //looks = rotate 'W' by cw 90 degrees 
#define RECOVER_HP 2 // heart
#define INVULNERABILITY 3 // shield
#define INCREASE_BPM 4 // Bullets per minute 

bool powerup_status;

Powerup Powerup_BulletSplit;
Powerup Powerup_Recover_Hp;
Powerup Powerup_Invulnerability;
Powerup Powerup_Increase_BPM;

Powerup Default;

void Asteroids_Init_Powerups(void)
{
	Default.height = 30.0f;
	Default.width = 30.0f;

	powerup_status = true;

	Powerup_BulletSplit.Sprite = CP_Image_Load("./Assets/Powerup_Bullet_Split_Sprite.png");

	Powerup_Recover_Hp.Sprite = CP_Image_Load("./Assets/Powerup_RecoverHealth_Sprite.png");

	Powerup_Invulnerability.Sprite = CP_Image_Load("./Assets/Powerup_Invunerability_Sprite.png");

	Powerup_Increase_BPM.Sprite = CP_Image_Load("./Assets/Powerup_Shootfaster_Sprite.png");

	Default.pos = Asteroids_Utility_Generate_Random_Pos();
	Default.type = Asteroids_Generate_Random_Powerup();

}

void Asteroids_Update_Powerups(void)
{
	Asteroids_Powerup_Time_Manager();

	Asteroids_Draw_Powerup();
	
	if (powerup_status == false)
		Asteroids_Init_Powerups();
}

void Asteroids_Draw_Powerup(void)
{
	if (powerup_status == true)
	{
		switch (Default.type)
		{
		case BULLET_SPLIT:
			CP_Image_Draw(Powerup_BulletSplit.Sprite, Default.pos.x, Default.pos.y, Default.width, Default.height, 255);
			break;
		case RECOVER_HP:
			CP_Image_Draw(Powerup_Recover_Hp.Sprite, Default.pos.x, Default.pos.y, Default.width, Default.height, 255);
			break;
		case INVULNERABILITY:
			CP_Image_Draw(Powerup_Invulnerability.Sprite, Default.pos.x, Default.pos.y, Default.width, Default.height, 255);
			break;
		case INCREASE_BPM:
			CP_Image_Draw(Powerup_Increase_BPM.Sprite, Default.pos.x, Default.pos.y, Default.width, Default.height, 255);
			break;
		default:
			break;
		}
	}
}
int Asteroids_Generate_Random_Powerup(void)
{
	int random_powerup = CP_Random_RangeInt(1, 4);
	return random_powerup;
}

void Asteroids_Powerup_Time_Manager(void)
{
	float CurrentElaspedTime = CP_System_GetDt();

	static float TotalElaspedTime = 0;

	TotalElaspedTime += CurrentElaspedTime;
	
	if (TotalElaspedTime >= 3.0f)
	{
		powerup_status = false;
		TotalElaspedTime = 0.0f;
	}

}