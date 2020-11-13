#include "powerup_interaction.h"

CP_Image Invulnerability;

extern bool powerup_lifespan;
extern bool invulnerable;

void Asteroids_Powerup_Player_Interaction_Init(void)
{
	Invulnerability = CP_Image_Load("./Assets/Invulnerability_Circle.png");
}

void Asteroids_Powerup_Player_Invulernability(Player* player)
{
	CP_Image_DrawAdvanced(Invulnerability, player->pos.x, player->pos.y, 54.0f, 54.0f, 255, 0.0f);
	//if(!powerup_lifespan)
	//	invulnerable = false;
}
	

void Asteroids_Powerup_Lifespan_Manager(Powerup* powerup)
{
	float dt = CP_System_GetDt();
	/*static float TotalElaspedTime = 0; // old code
	TotalElaspedTime += dt;*/ // old code


	powerup->lifespan -= dt; // starts from 10.0f, minus dt every frame.

	if (powerup->lifespan < 0) //if lifespan reaches 0
	{
		powerup->status = false; // set status to false, i.e: powerup effect stops
	}
}
