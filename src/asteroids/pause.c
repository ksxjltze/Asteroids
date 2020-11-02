#include "pause.h"

bool paused = false;

CP_Vector position;
float width, height;

CP_Color backgroundColor;
Button btnContinue;

void Asteroids_Pause_Init()
{
	position = Asteroids_Utility_GetWindowMiddle();
	width = 0, height = 0;

	backgroundColor = CP_Color_Create(0, 0, 0, 255);

	CP_Vector btnContinuePos = Asteroids_Utility_GetWindowMiddle();
	btnContinue = Asteroids_Button_Add_New_Button(btnContinuePos, 200, 200);
	Asteroids_Button_Set_Text(&btnContinue, 20, "Continue");

}

void Asteroids_Pause_CheckInput()
{
	if (CP_Input_KeyTriggered(ASTEROIDS_PAUSE_KEY))
	{
		Asteroids_Pause_Toggle();
	}
}

void Asteroids_Pause_Update()
{
	if (paused)
	{
		Asteroids_Pause_DisplayMenu();
	}
}

void Asteroids_Pause_Toggle()
{
	paused = !paused;
}

bool Asteroids_Pause_GetStatus()
{
	return paused;
}

void Asteroids_Pause_DisplayMenu()
{
	CP_Settings_Background(backgroundColor);
	Asteroids_Pause_Buttons_Update();
}

void Asteroids_Pause_Buttons_Update()
{
	Asteroids_Button_Update(&btnContinue);
}