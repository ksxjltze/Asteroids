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