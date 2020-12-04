//---------------------------------------------------------
// file:	splash.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Splash screen source file.
//			Draws the DigiPen splash logo for a specified duration.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "constants.h"
#include "splash.h"

int Asteroids_Splash_Draw(float duration, CP_Image splash_image)
{
	//splash
	if (CP_System_GetSeconds() < duration)
	{
		CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
		CP_Image_Draw(splash_image, WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f, (float)CP_Image_GetWidth(splash_image), (float)CP_Image_GetHeight(splash_image), 255);
		return 1;
	}
	return 0;
}