//---------------------------------------------------------
// file:	skin_menu.h
// author:	Lee Jia Keat
// contributors: Liu Ke (Additional Skins)
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Skin menu header file.
//			Handles Initialization, Loading, Selecting and Saving of skins.
//			Reads and Writes from a specific file to read and save player skins.
//			Displays a user interface for swapping skins.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "cprocessing.h"

typedef struct Skins
{
	CP_Image sprite;
	const char* name;
	float cost;
}Skin;

extern Skin current_skin;

void Asteroids_Skin_Menu_Init(void);
void Asteroids_Skin_Menu_Update(void);
void Asteroids_Skin_Menu_Draw(void);
void Asteroids_Skin_Menu_Load_Selected_Skin();
void Asteroids_Skin_Menu_Load_Skin(const char* path, const char* skin_name, float cost);
void Asteroids_Skin_Menu_Load_Default(void);
void Asteroids_Skin_Menu_Next_Skin(void);
void Asteroids_Skin_Menu_Read_Selected_Skin();
void Asteroids_Skin_Menu_Write_Selected_Skin();