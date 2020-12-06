//---------------------------------------------------------
// file:	help.c
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the guide screen available at the main menu.
//			Draws to the screen an overlay depending on the page number.
//			Overlay offers helpful instructions for the player
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
#include <math.h>
#include "final_boss.h"
#include "enemy.h"
#include "constants.h"


#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 75
#define BTN_TEXTSIZE 75
#define respawnTimer 2
#define FIRST_PAGE 0
#define LAST_PAGE 5
#define MODEL_COUNT 6
#define POWERUP_COUNT 5
Help_screen screen;

CP_Image Page_Image[LAST_PAGE];
CP_Image playerModel[MODEL_COUNT];
CP_Image powerupModel[POWERUP_COUNT];

CP_Image Display;

Button BackBtn, NextBtn, ExitBtn;

enum HELP_SCREEN { CONTROLS, MECHANICS, OBSTACLES, FINALBOSS, UPGRADES };

static float current_lifespan = 0.5f;
static float warning_lifespan = 0.5f;
static float spawn_animation_lifespan;
static float spawn_animation_lifespan_max;
static float respawnTimer1;
static float respawnTimer2;


Enemy helpEnemy[1];
Enemy helpEnemy2[1];

void Asteroids_Help_Screen_Init(void)
{
	for (int i = 0; i < LAST_PAGE; i++)
	{
		char path[100];
		sprintf_s(path, 100, "./Assets/Control_screen%d.png", i);
		Page_Image[i] = CP_Image_Load(path);
	}

	for (int i = 0; i < MODEL_COUNT; i++)
	{
		char spritePath[100];
		sprintf_s(spritePath, 100, "./Assets/Spaceship%d.png", i +1);
		playerModel[i] = CP_Image_Load(spritePath);
	}

	for (unsigned int i = 0; i < POWERUP_COUNT; i++)
	{
		char spritePath[100];
		sprintf_s(spritePath, 100, "./Assets/powerup_sprite%d.png", i + 1);
		powerupModel[i] = CP_Image_Load(spritePath);
	}

	Display = CP_Image_Load("./Assets/newasteroids.png");
	screen.overlay = FIRST_PAGE;
	warning_lifespan = 2.0f;
	warning_lifespan = 2.0f;
	respawnTimer1 = 0;
	respawnTimer2 = 0;
	spawn_animation_lifespan = ASTEROIDS_FINAL_BOSS_SUMMON_ANIMATION_TIMER;
	spawn_animation_lifespan_max = ASTEROIDS_FINAL_BOSS_SUMMON_ANIMATION_TIMER;
	Asteroids_Audio_Manager_Init();

	screen.width = (float)CP_System_GetWindowWidth();
	screen.height = (float)CP_System_GetWindowHeight();
	screen.pos = Asteroids_Utility_GetWindowMiddle();
	screen.Image = Page_Image[screen.overlay];

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
	Asteroids_Final_Boss_Init();
	particle_init();
	Asteroids_Particle_Dot_Init();
	explosion_init();
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
	if(screen.overlay < LAST_PAGE)
		CP_Image_Draw(Page_Image[screen.overlay], screen.pos.x, screen.pos.y, screen.width, screen.height, 255);

	if (screen.overlay > FIRST_PAGE)
		Asteroids_Button_Update(&BackBtn);

	if (screen.overlay < LAST_PAGE -1)
		Asteroids_Button_Update(&NextBtn);


	switch (screen.overlay)
	{
	case CONTROLS:
		Asteroids_Help_Draw_Controls_Screen();
		break;
	case OBSTACLES:
		Asteroids_Help_Draw_Obstacle_Screen();
		break;
	case FINALBOSS:
		Asteroids_Help_Draw_FinalBoss_Screen();
		break;
	default:
		break;
	}
}
void Asteroids_Help_Draw_Obstacle_Screen(void)
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
	Asteroids_Help_Update_Enemies();
	particle_update();
	Asteroids_Particle_Draw_Dot();
	Asteroids_Draw_Obstacle(&Blackhole);
	Asteroids_Draw_Obstacle(&GammaRay);
	Asteroids_Help_Sreen_Draw_Warning();
	Asteroids_Help_Menu_Spawn_Static_Enemies();
}

void Asteroids_Help_Draw_Controls_Screen(void)
{
	static float rotation = 0;
	static float rotation_rate = 20.0f;
	rotation += (rotation_rate * CP_System_GetDt());
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		CP_Image_DrawAdvanced(playerModel[i], 50.0f + (125.0f * i), 150.0f, 100, 100, 255, rotation);
	}
	for (int i = 0; i < POWERUP_COUNT; i++)
	{
		int y = 480;
		if (i % 2 != 0)
			y = 600;
		CP_Image_DrawAdvanced(powerupModel[i], 75.0f + (125.0f * i), (float)y, 50, 50, 255, rotation);
	}
}

void Asteroids_Help_Update_Enemies(void)
{
	Enemy* d1 = helpEnemy;
	Enemy* d2 = helpEnemy2;
	if (d1->active)
	{
		CP_Image_DrawAdvanced(Display, d1->pos.x, d1->pos.y, d1->collider.diameter, d1->collider.diameter, 255, d1->rotate_rate);
		Asteroids_Check_Collision_Blackhole_Enemy_Player(d1, NULL, &Blackhole, 1);
	}
	if (d2->active)
	{
		CP_Image_DrawAdvanced(Display, d2->pos.x, d2->pos.y, d2->collider.diameter, d2->collider.diameter, 255, d2->rotate_rate);
		Asteroids_Check_Collision_Gammaray_Enemy_Player(d2, NULL, &GammaRay, 1);
	}
}

void Asteroids_Help_Draw_FinalBoss_Screen(void)
{
	Asteroids_Help_Draw_FinalBoss_Spawn_Animation();
}
void Asteroids_Help_Screen_IncreasePageNo(void)
{
	if (screen.overlay >= LAST_PAGE)
		return;

	screen.overlay += 1;
}

void Asteroids_Help_Screen_DecreasePageNo(void)
{
	if (screen.overlay <= FIRST_PAGE)
		return;

	screen.overlay -= 1;
}

void Asteroids_Help_Sreen_Draw_Warning(void)
{
	float dt = CP_System_GetDt();
	current_lifespan -= dt;

	CP_Image_Draw(Warning, (float)WIN_WIDTH /2 , ((float)(WIN_HEIGHT) *  0.75f), (float)WIN_WIDTH, 80.0f, (int)(fabsf(current_lifespan) / warning_lifespan * 255));
	if (current_lifespan < -warning_lifespan)
	{
		current_lifespan = warning_lifespan;
	}
}

void Asteroids_Help_Draw_FinalBoss_Spawn_Animation(void)
{
	float dt = CP_System_GetDt();
	spawn_animation_lifespan -= dt;

	CP_Image_Draw(Final_Boss_Spawn_Animation, (float)WIN_WIDTH / 2, ((float)(WIN_HEIGHT) * 0.28f), 200.0f, 200.0f, (int)(fabsf(spawn_animation_lifespan) / spawn_animation_lifespan_max * 255));
	if (spawn_animation_lifespan < -spawn_animation_lifespan_max)
	{
		spawn_animation_lifespan = spawn_animation_lifespan_max;
	}
}

void Asteroids_Help_Menu_Spawn_Static_Enemies(void)
{
	Enemy* d1 = helpEnemy;
	Enemy* d2 = helpEnemy2;
	if (!d1->active)
	{
		respawnTimer1 -= CP_System_GetDt();
		if (respawnTimer1 <= 0)
		{
			d1 = Asteroids_Enemy_Spawn(helpEnemy, 1, CP_Vector_Set((float)WIN_WIDTH * 0.75f, Blackhole.pos.y));
			respawnTimer1 = respawnTimer;
		}
	}
	if (!d2->active)
	{
		respawnTimer2 -= CP_System_GetDt();
		if (respawnTimer2 <= 0)
		{
			d2 = Asteroids_Enemy_Spawn(helpEnemy2, 1, CP_Vector_Set((float)WIN_WIDTH * 0.75f, GammaRay.pos.y));
			respawnTimer2 = respawnTimer;
		}
	}
}