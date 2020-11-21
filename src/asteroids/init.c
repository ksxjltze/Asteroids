#include "init.h"
#include <stdlib.h>
#include <time.h>

void Asteroids_Settings_Setup(int win_width, int win_height) {
	srand((int)time(0)); //random seed
	CP_System_SetWindowSize(win_width, win_height);

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_Settings_TextSize(50);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_System_SetFrameRate(60);
}

void Asteroids_Menu_Settings_Setup(int win_width, int win_height)
{
	CP_System_SetWindowSize(win_width, win_height);
	CP_System_Fullscreen();

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_Settings_TextSize(50);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_System_SetFrameRate(60);
}