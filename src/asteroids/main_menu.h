//---------------------------------------------------------
// file:	main_menu.h
// author:	Bryan Koh Yan Wei
// contributors: Lee Jia Keat (Difficulty, Skin, Leaderboard and Upgrade Menus), Liu Ke (UI Design)
// email:	, l.jiakeat@digipen.edu, 
//
// brief:	Main menu header file.
//			Handles Initialization, Updating and Drawing of the Main Menu/Title Screen.
//			Contains functions to display other sub menus (overlays) as well as buttons to toggle them.
//			Is the entry point into the main game, as well as the screen where settings such as difficulty can be set from.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "main_menu.h"
#include "game.h"
#include "cprocessing.h"
#include "constants.h"
#include "init.h"
#include "button.h"
#include <stdbool.h>
#include "audio_manager.h"

extern DIFFICULTY ASTEROIDS_GAME_DIFFICULTY;

// ENTRY POINT
void Asteroids_MainMenu_Init(void);
void Asteroids_MainMenu_Update(void);
void Asteroids_MainMenu_Exit(void);


//GENERAL 
void Asteroids_Draw_MainMenu(void);
void Asteroids_MainMenu_Button_Init(void);
void Asteroids_MainMenu_CheckInput(void);


// MAIN MENU DISPLAYS
void Asteroids_Play_Game(void);
void Asteroids_MainMenu_Guide(void);
void Asteroids_QuitGame(void);
void Asteroids_Credits_Enter(void);
void Asteroids_Display_LeaderBoard(void);
void Asteroids_Exit_Screen(void);
void Asteroids_Menu_Display_VolumeONOFF(void);

//BACKGROUND
void Asteroids_MainMenu_Update_Background(void);
void Asteroids_MainMenu_Draw_Background(CP_Image image);

//DIFFICULTY MENU
void Asteroids_Menu_Display_DifficultyMenu(void);

//SKIN MENU
void Asteroids_Menu_Display_SkinMenu(void);
void Asteroids_MainMenu_Draw_Current_Ship();
float Asteroids_MainMenu_Rotation_Towards_Mouse();

//UPGRADES MENU
void Asteroids_Menu_Display_UpgradesMenu(void);

//SETTINGS
void Asteroids_MainMenu_Set_FullScreen(void);
