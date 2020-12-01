//---------------------------------------------------------
// file:	difficulty_menu.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
// brief:	Difficulty Menu header file.
//			Contains functions that initializes,
//			updates and draws the Difficulty Menu User Interface.
//			Enables setting game difficulty through buttons.
//			Reads and Writes selected difficulty option to and from
//			a specific text file.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"
#include "main_menu.h"

void Asteroids_Difficulty_Menu_Init(void);
void Asteroids_Difficulty_Menu_Update(void);
void Asteroids_Difficulty_Menu_Draw(void);
void Asteroids_Difficulty_Set_NextDifficulty(Button* button);
void Asteroids_Difficulty_Menu_Update_ButtonText(Button* button);
void Asteroids_Difficulty_Save_To_File(void);
void Asteroids_Difficulty_Get_From_File(void);