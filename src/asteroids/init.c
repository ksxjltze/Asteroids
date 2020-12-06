//---------------------------------------------------------
// file:	init.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	File for initializing and setting CProcessing settings.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "init.h"
#include <stdlib.h>
#include <time.h>
#include "constants.h"

void Asteroids_Menu_Settings_Setup(int win_width, int win_height)
{
	CP_System_SetWindowSize(win_width, win_height);
	if (FULLSCREEN)
		CP_System_Fullscreen();

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_Settings_TextSize(50);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_System_SetFrameRate(60);
}