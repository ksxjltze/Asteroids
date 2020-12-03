#include "pause.h"
#include "final_boss.h"
bool paused = false;

CP_Vector position;

CP_Color backgroundColor;
Button btnContinue;
Button btnQuit;

void Asteroids_Pause_Init()
{
	position = Asteroids_Utility_GetWindowMiddle();
	float btnWidth = 600, btnHeight = 100;
	float textSize = 50.0f;

	backgroundColor = CP_Color_Create(0, 0, 0, 255);

	btnContinue = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	CP_Vector btnContinuePos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnContinue.width / 2, CP_System_GetWindowHeight() * 0.3f - btnContinue.height / 2);
	Asteroids_Button_Set_Position(&btnContinue, btnContinuePos);
	Asteroids_Button_Set_Text(&btnContinue, textSize, "Continue");
	Asteroids_Button_Set_Callback_Void(&Asteroids_Pause_Continue, &btnContinue);

	btnQuit = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	CP_Vector btnQuitPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnQuit.width / 2, CP_System_GetWindowHeight() * 0.6f - btnQuit.height);
	Asteroids_Button_Set_Position(&btnQuit, btnQuitPos);
	Asteroids_Button_Set_Text(&btnQuit, textSize, "Quit");
	Asteroids_Button_Set_Callback_Void(&Asteroids_Pause_QuitGame, &btnQuit);

}

void Asteroids_Pause_QuitGame()
{
	paused = false;
	Asteroids_Final_Boss_Reset();
	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
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

void Asteroids_Pause_Continue()
{
	paused = false;
}

void Asteroids_Pause_DisplayMenu()
{
	CP_Settings_Background(backgroundColor);
	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("Paused", (float)WIN_WIDTH / 2, 100);
	Asteroids_Pause_Buttons_Update();
}

void Asteroids_Pause_Buttons_Update()
{
	Asteroids_Button_Update(&btnContinue);
	Asteroids_Button_Update(&btnQuit);
}