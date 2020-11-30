#pragma once
#include "main_menu.h"
#include "game.h"
#include "cprocessing.h"
#include "constants.h"
#include "init.h"
#include "button.h"
#include <stdbool.h>

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
void Asteroids_Controls(void);
void Asteroids_QuitGame(void);
void Asteroids_Credits(void);
void Asteroids_Display_LeaderBoard(void);
void Asteroids_Exit_Screen(void);

//BACKGROUND
void Asteroids_MainMenu_Update_Background(void);
void Asteroids_MainMenu_Draw_Background(void);

//DIFFICULTY MENU
void Asteroids_Menu_Display_DifficultyMenu(void);

//SKIN MENU
void Asteroids_Menu_Display_SkinMenu(void);
void Asteroids_MainMenu_Draw_Current_Ship();
float Asteroids_MainMenu_Rotation_Towards_Mouse();

//UPGRADES MENU
void Asteroids_Menu_Display_UpgradesMenu(void);
