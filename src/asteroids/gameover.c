#include "gameover.h"
#include "button.h"
#include "game.h"

Button btnRestart;
Button btnQuit; //return to main menu

void Asteroids_GameOver_Init(void)
{
	float btnWidth = 600, btnHeight = 100;
	float textSize = 80.0f;

	btnRestart = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	CP_Vector btnRestartPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnRestart.width / 2, CP_System_GetWindowHeight() * 0.3f - btnRestart.height / 2);
	Asteroids_Button_Set_Position(&btnRestart, btnRestartPos);
	Asteroids_Button_Set_Text(&btnRestart, textSize, "Restart");
	Asteroids_Button_Set_Callback(&Asteroids_GameOver_Restart, &btnRestart);
	
	CP_Vector btnExitPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnRestart.width / 2, CP_System_GetWindowHeight() * 0.6f - btnRestart.height / 2);
	btnQuit = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	Asteroids_Button_Set_Position(&btnQuit, btnExitPos);
	Asteroids_Button_Set_Text(&btnQuit, textSize, "Quit");
	Asteroids_Button_Set_Callback(&Asteroids_GameOver_Quit, &btnQuit);
}

void Asteroids_GameOver_Restart()
{
	CP_Engine_SetNextGameState(Asteroids_Init, Asteroids_Update, Asteroids_Exit);
}

void Asteroids_GameOver_Quit()
{
	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
}

void Asteroids_GameOver_Update(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("GAME OVER", (float)WIN_WIDTH / 2, 100);
	
	Asteroids_Button_Update(&btnRestart);
	Asteroids_Button_Update(&btnQuit);
}

void Asteroids_GameOver_Exit(void)
{

}