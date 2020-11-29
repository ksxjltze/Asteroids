#include "gameover.h"
#include "button.h"
#include "game.h"
#include "score.h"
#include "audio_manager.h"

Button btnRestart;
Button btnQuit; //return to main menu

static char str_time_score[20];
static char str_kill_score[20];

void Asteroids_GameOver_Init(void)
{
	float btnWidth = 300, btnHeight = 100;
	float textSize = 80.0f;

	Asteroids_GameOver_Init_Score();

	btnRestart = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	CP_Vector btnRestartPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnRestart.width / 2, CP_System_GetWindowHeight() * 0.6f - btnRestart.height / 2);
	Asteroids_Button_Set_Position(&btnRestart, btnRestartPos);
	Asteroids_Button_Set_Text(&btnRestart, textSize, "Restart");
	Asteroids_Button_Set_Callback_Void(&Asteroids_GameOver_Restart, &btnRestart);
	
	CP_Vector btnExitPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnRestart.width / 2, CP_System_GetWindowHeight() * 0.8f - btnRestart.height / 2);
	btnQuit = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	Asteroids_Button_Set_Position(&btnQuit, btnExitPos);
	Asteroids_Button_Set_Text(&btnQuit, textSize, "Quit");
	Asteroids_Button_Set_Callback_Void(&Asteroids_GameOver_Quit, &btnQuit);

	Asteroids_Audio_Manager_Init();
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
	CP_Font_DrawText("GAME OVER", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.1f);
	Asteroids_GameOver_Display_Score();
	
	Asteroids_Button_Update(&btnRestart);
	Asteroids_Button_Update(&btnQuit);
}

void Asteroids_GameOver_Init_Score(void)
{
	sprintf_s(str_time_score, 20, "Time: %.2fs", Score.time_score);
	sprintf_s(str_kill_score, 20, "Destroyed: %d", Score.enemy_kill_score);
}

void Asteroids_GameOver_Display_Score(void)
{
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText(str_time_score, (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.3f);
	CP_Font_DrawText(str_kill_score, (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.4f);
}

void Asteroids_GameOver_Exit(void)
{
	Asteroids_Audio_Manager_Exit();
}