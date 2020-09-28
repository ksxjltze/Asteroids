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
#include "constants.h"

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	win_width = (int*)malloc(sizeof(int));
	win_height = (int*)malloc(sizeof(int));
	splash_duration = (float*)malloc(sizeof(float));

	max_velocity = (float*)malloc(sizeof(float));
	speed = (int*)malloc(sizeof(int));

	bullet_speed = (int*)malloc(sizeof(int));
	fire_rate = (float*)malloc(sizeof(float));
	hurt_window = (float*)malloc(sizeof(float));

	//health bar
	bar_width = (float*)malloc(sizeof(float));
	bar_height = (float*)malloc(sizeof(float));

	*win_width = 1280;
	*win_height = 720;
	*splash_duration = 2.0f;

	*max_velocity = 10.0f; //pixels per second
	*speed = 10;

	*bullet_speed = 1000;
	*fire_rate = 300.0f; //bullets per minute
	*hurt_window = 0.1f; //seconds

	//health bar
	*bar_width = 200;
	*bar_height = 20;

	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
