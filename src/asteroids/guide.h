#pragma once
//---------------------------------------------------------
// file:	guide.h
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//			
// brief:	Code relating to the guide screen available at the main menu.
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include <stdbool.h>

typedef struct Help_Screen
{
	int overlay;
	CP_Vector pos;
	float width, height;
}Help_screen;

typedef struct DisplayModel
{
	float x, y;
	float width, height;
	float offsetX, offsetY;
}DisplayModel;


/*				GUIDE SCREEN MAIN ENTRY POINTS		*/
void Asteroids_Help_Screen_Init(void);
void Asteroids_Help_Screen_Update(void);
void Asteroids_Help_Screen_Exit(void);
void Asteroids_Help_Initialize_Model_Sizing(void);


/*				GUIDE SCREEN DRAWING FUNCTIONS */
void Asteroids_Draw_Screen_Page(void);



//				CONTROLS/MODELS PAGE
void Asteroids_Help_Draw_Controls_Screen(void);



//				OBSTACLE ENVIRONMENT PAGE
void Asteroids_Help_Draw_Obstacle_Screen(void);
void Asteroids_Help_Update_Enemies(void);
void Asteroids_Help_Sreen_Draw_Warning(void);


//				FINAL BOSS PAGE
void Asteroids_Help_Draw_FinalBoss_Screen(void);
void Asteroids_Help_Draw_FinalBoss_Spawn_Animation(void);



/*				GUIDE MENU HELPER FUNCTIONS				*/
void Asteroids_Help_Screen_Exit_ToMenu(void);
void Asteroids_Help_Screen_IncreasePageNo(void);
void Asteroids_Help_Screen_DecreasePageNo(void);
void Asteroids_Help_Menu_Spawn_Static_Enemies(void);
void Asteroids_Help_Menu_Despawn_Static_Enemies(void);