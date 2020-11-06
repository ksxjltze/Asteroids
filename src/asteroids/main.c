//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "game.h"
#include "main_menu.h"
#include "splash.h"
#include "constants.h"

CP_Image splash;

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation

void main_init(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	Asteroids_Menu_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);
	splash = CP_Image_Load("./Assets/DigiPen_WHITE.png");

}

void main_update(void)
{
	if (Asteroids_Splash_Draw(SPLASH_DURATION, splash))
		return;

	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
	CP_Engine_Run();
}

void main_exit(void)
{

}

int main(void)
{
	CP_System_ShowConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	CP_Engine_SetNextGameState(main_init, main_update, main_exit);
	CP_Engine_Run();
	return 0;
}
