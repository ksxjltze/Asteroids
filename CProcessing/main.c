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
#include "menu.h"
#include "splash.h"
#include "constants.h"

extern const int WIN_WIDTH = 1280;
extern const int WIN_HEIGHT = 720;
extern const float SPLASH_DURATION = 3.0f;

extern const float MAX_VELOCITY = 10.0f; //pixels per second
extern const int SPEED = 10;

extern const int BULLET_SPEED = 1000;
extern const float FIRE_RATE = 600.0f; //bullets per minute
extern const float HURT_WINDOW = 0.1f; //seconds
extern const float BULLET_DAMAGE = 1;
extern const float ENEMY_HP = 3;

//health bar
extern const float BAR_WIDTH = 100;
extern const float BAR_HEIGHT = 10;
extern const float BAR_OFFSET_Y = 10;

extern const char* PLAYER_SPRITE_PATH = "./Assets/spaceship1.png";
extern const float PLAYER_MAX_HP = 3;

extern const float PLAYER_MAX_FUEL = 100.0f;
extern const float DRAIN_RATE = 5.0f;

CP_Image splash;

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation

void main_init(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	init_menu_settings(WIN_WIDTH, WIN_HEIGHT);
	splash = CP_Image_Load("./Assets/DigiPen_WHITE.png");

}

void main_update(void)
{
	if (display_splash(SPLASH_DURATION, splash))
		return;

	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
	CP_Engine_Run();
}

void main_exit(void)
{

}



int main(void)
{
	CP_Engine_SetNextGameState(main_init, main_update, main_exit);
	CP_Engine_Run();
	return 0;
}
