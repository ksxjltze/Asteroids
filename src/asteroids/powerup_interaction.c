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
	if (!powerup_lifespan)
		invulnerable = false;
}

void Asteroids_Powerup_Lifespan_Manager(void)
{
	float dt = CP_System_GetDt();
	static float TotalElaspedTime = 0;
	TotalElaspedTime += dt;

	printf("dt is %.2f\n", TotalElaspedTime);

	if (TotalElaspedTime >= 30.0f)
	{
		powerup_lifespan = false;
		TotalElaspedTime = 0.0f;
	}
}
