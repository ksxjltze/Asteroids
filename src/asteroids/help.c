//---------------------------------------------------------
// file:	help.c
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the help screen available at the main menu.
//			
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "help.h"
#include "utility.h"
#include "button.h"
#include "main_menu.h"
#include "audio_manager.h"
#include <string.h>
#include "obstacles.h"
#include "enemy.h"

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 75
#define BTN_TEXTSIZE 75

Help_screen screen;

#define FIRST_PAGE 0
#define LAST_PAGE 4

CP_Image Page_Image[LAST_PAGE];

Button BackBtn, NextBtn, ExitBtn;

enum HELP_SCREEN { CONTROLS, MECHANICS, OBSTACLES, FINALBOSS, UPGRADES };

static float warning_lifespan;
static float warning_lifespan_max;

void Asteroids_Help_Screen_Init(void)
{
	for (int i = 0; i < LAST_PAGE; i++)
	{
		char path[100];
		sprintf_s(path, 100, "./Assets/Control_screen%d.png", i);
		Page_Image[i] = CP_Image_Load(path);
	}

	screen.id = FIRST_PAGE;
	warning_lifespan = 2.0f;
	warning_lifespan = 2.0f;
	Asteroids_Audio_Manager_Init();

	screen.width = (float)CP_System_GetWindowWidth();
	screen.height = (float)CP_System_GetWindowHeight();
	screen.pos = Asteroids_Utility_GetWindowMiddle();
	screen.Image = Page_Image[screen.id];

	BackBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	NextBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	ExitBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);

	Asteroids_Button_Set_Text(&BackBtn, BTN_TEXTSIZE, "Back");
	Asteroids_Button_Set_Text(&NextBtn, BTN_TEXTSIZE, "Next");
	Asteroids_Button_Set_Text(&ExitBtn, BTN_TEXTSIZE, "Exit");

	CP_Vector position_offset = Asteroids_Utility_GetWindowMiddle();

	CP_Vector ExitBtnPos = CP_Vector_Set(position_offset.x - BUTTON_WIDTH / 2, (float)WIN_HEIGHT - BUTTON_HEIGHT);
	CP_Vector BackBtnPos = CP_Vector_Set(0, position_offset.y - BUTTON_HEIGHT / 2);
	CP_Vector NextBtnPos = CP_Vector_Set((float)WIN_WIDTH - BUTTON_WIDTH, position_offset.y - BUTTON_HEIGHT / 2);

	Asteroids_Button_Set_Position(&BackBtn, BackBtnPos);
	Asteroids_Button_Set_Position(&NextBtn, NextBtnPos);
	Asteroids_Button_Set_Position(&ExitBtn, ExitBtnPos);

	Asteroids_Button_Set_Callback_Void(&Asteroids_Help_Screen_Exit_ToMenu, &ExitBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Help_Screen_IncreasePageNo, &NextBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Help_Screen_DecreasePageNo, &BackBtn);

	Asteroids_Obstacles_Init();
}
void Asteroids_Help_Screen_Update(void)
{
	Asteroids_Draw_Screen_Page();
	Asteroids_Button_Update(&ExitBtn);
}
void Asteroids_Help_Screen_Exit(void)
{

}

void Asteroids_Help_Screen_Exit_ToMenu(void)
{
	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
}

void Asteroids_Draw_Screen_Page(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	if(screen.id < LAST_PAGE)
		CP_Image_Draw(Page_Image[screen.id], screen.pos.x, screen.pos.y, screen.width, screen.height, 255);

	if (screen.id > FIRST_PAGE)
		Asteroids_Button_Update(&BackBtn);

	if (screen.id < LAST_PAGE -1)
		Asteroids_Button_Update(&NextBtn);
	Asteroids_Draw_Obstacle_Screen();
}
void Asteroids_Draw_Obstacle_Screen(void)
{
	if (screen.id == OBSTACLES)
	{
		if (Blackhole.active == false)
				{
					Asteroids_Obstacle_Spawn_Tutorial(&Blackhole, ASTEROIDS_OBSTACLE_BLACKHOLE_SPEED, ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH,
					ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH, CP_Vector_Set(0, (float)(WIN_HEIGHT / 3) - ASTEROIDS_OBSTACLE_BLACKHOLE_WIDTH));
					Blackhole.Collider2.diameter = Blackhole.width;
				}
		if (GammaRay.active == false)
		{
			Asteroids_Obstacle_Spawn_Tutorial(&GammaRay, ASTEROIDS_OBSTACLE_GAMMARAY_SPEED, ASTEROIDS_OBSTACLE_GAMARAY_HEIGHT,
				(float)(WIN_WIDTH / 4), CP_Vector_Set(0, (float)(WIN_HEIGHT / 3) + ASTEROIDS_OBSTACLE_GAMARAY_HEIGHT));
			GammaRay.Collider.height = GammaRay.height;
			GammaRay.Collider.width = GammaRay.width;
		}

		Asteroids_Help_Update_Obstacle_Pos(&Blackhole, CP_System_GetDt());
		Asteroids_Help_Update_Obstacle_Pos(&GammaRay, CP_System_GetDt());

		Asteroids_Draw_Obstacle(&Blackhole);
		Asteroids_Draw_Obstacle(&GammaRay);

	}
}
void Asteroids_Help_Screen_IncreasePageNo(void)
{
	if (screen.id >= LAST_PAGE)
		return;

	screen.id += 1;
}

void Asteroids_Help_Screen_DecreasePageNo(void)
{
	if (screen.id <= FIRST_PAGE)
		return;

	screen.id -= 1;
}

//void Asteroids_Help_Sreen_Draw_Warning(void)
//{
//	float dt = CP_System_GetDt();
//	current_lifespan -= dt;
//
//	CP_Image_Draw(Warning, (float)WIN_WIDTH / 2, GammaRay.pos.y, (float)WIN_WIDTH, 80.0f, (int)(fabsf(current_lifespan) / warning_lifespan * 255));
//	if (current_lifespan < -warning_lifespan)
//	{
//		current_lifespan = warning_lifespan;
//	}
//}

