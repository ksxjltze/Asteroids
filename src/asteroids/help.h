#pragma once
//---------------------------------------------------------
// file:	help.h
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the help screen available at the main menu.
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include <stdbool.h>

typedef struct Help_Screen
{
	int id;
	CP_Vector pos;
	CP_Image Image;
	float width, height;
}Help_screen;

void Asteroids_Help_Screen_Init(void);
void Asteroids_Help_Screen_Update(void);
void Asteroids_Help_Screen_Exit(void);
void Asteroids_Help_Screen_Exit_ToMenu(void);

void Asteroids_Draw_Screen_Page(void);
void Asteroids_Help_Draw_Obstacle_Screen(void);
void Asteroids_Help_Draw_FinalBoss_Screen(void);
void Asteroids_Help_Draw_FinalBoss_Spawn_Animation(void);

void Asteroids_Help_Screen_IncreasePageNo(void);
void Asteroids_Help_Screen_DecreasePageNo(void);
void Asteroids_Help_Sreen_Draw_Warning(void);

void Asteroids_Help_Menu_Spawn_Static_Enemies(void);