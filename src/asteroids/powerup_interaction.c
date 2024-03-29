//---------------------------------------------------------
// file:	powerup_interaction.c
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the powerup interaction.
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "powerup_interaction.h"

CP_Image Invulnerability;

extern bool invulnerable;

void Asteroids_Powerup_Player_Interaction_Init(void)
{
	Invulnerability = CP_Image_Load("./Assets/Invulnerability_Circle.png");
}

void Asteroids_Powerup_Player_Invulernability(Player* player)
{
	if(invulnerable)
		CP_Image_DrawAdvanced(Invulnerability, player->pos.x, player->pos.y, 54.0f, 54.0f, 255, 0.0f);
}