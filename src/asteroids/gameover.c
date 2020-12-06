//---------------------------------------------------------
// file:	gameover.c
// author:	Lee Jia Keat
// contributors: Bryan Koh Yan Wei (Display score)
// email:	l.jiakeat@digipen.edu, 
// brief:	Game Over scene source file, handles the game over scene.
//			Displays the player's score (Asteroids destroyed and time survived)
//			and provides buttons to retry the game or exit to title screen.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "gameover.h"
#include "button.h"
#include "game.h"
#include "score.h"
#include "audio_manager.h"
#include "final_boss.h"
#include "leaderboard.h"
#include <stdbool.h>
#include "final_boss.h"

Button btnRestart;
Button btnQuit; //return to main menu

static float deleteTimer; //Characters per second
static bool scoreSaved;

static char str_time_score[20];
static char str_kill_score[20];

#define NAME_TEXT_SIZE 50.0f

//JIA KEAT
void Asteroids_GameOver_Init(void)
{
	float btnWidth = 300, btnHeight = 100;
	float textSize = 80.0f;

	CURRENT_SCORE.stage = ASTEROIDS_GAME_DIFFICULTY;
	Asteroids_GameOver_Init_Score();
	Asteroids_Leaderboard_Init();

	btnRestart = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	CP_Vector btnRestartPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnRestart.width / 2, CP_System_GetWindowHeight() * 0.65f - btnRestart.height / 2);
	Asteroids_Button_Set_Position(&btnRestart, btnRestartPos);
	Asteroids_Button_Set_Text(&btnRestart, textSize, "Restart");
	Asteroids_Button_Set_Callback_Void(&Asteroids_GameOver_Restart, &btnRestart);
	
	CP_Vector btnExitPos = CP_Vector_Set(CP_System_GetWindowWidth() * 0.5f - btnRestart.width / 2, CP_System_GetWindowHeight() * 0.85f - btnRestart.height / 2);
	btnQuit = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	Asteroids_Button_Set_Position(&btnQuit, btnExitPos);
	Asteroids_Button_Set_Text(&btnQuit, textSize, "Quit");
	Asteroids_Button_Set_Callback_Void(&Asteroids_GameOver_Quit, &btnQuit);

	scoreSaved = false;
	deleteTimer = 0;

	Asteroids_Audio_Manager_Init();
	Asteroids_Final_Boss_Reset();
	Asteroids_Audio_Manager_BGM_GameOver_Play();
}

void Asteroids_GameOver_CheckInput()
{
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		if (scoreSaved == false)
		{
			scoreSaved = true;
			Asteroids_Leaderboard_Insert_Score(CURRENT_SCORE);
		}
	}

	if (scoreSaved)
		return;

	for (int i = KEY_0; i <= KEY_Z; i++)
	{
		if (i > KEY_9 && i < KEY_A)
			continue;

		if (CP_Input_KeyTriggered(i))
		{
			size_t length = strlen(CURRENT_SCORE.name);
			if (length < NAME_MAX_SIZE - 1)
			{
				if (i <= KEY_9)
					CURRENT_SCORE.name[length] = (char)i;
				else if (CP_Input_KeyDown(KEY_LEFT_SHIFT))
					CURRENT_SCORE.name[length] = (char)i;
				else
					CURRENT_SCORE.name[length] = (char)(i + 'a' - 'A');
					
				CURRENT_SCORE.name[length + 1] = 0;
			}
			break;
		}
	}

	if (CP_Input_KeyDown(KEY_BACKSPACE))
	{
		if (deleteTimer > ASTEROIDS_INPUT_BACKSPACE_DELETE_SPEED || CP_Input_KeyTriggered(KEY_BACKSPACE))
		{
			size_t length = strlen(CURRENT_SCORE.name);
			if (length > 0)
			{
				CURRENT_SCORE.name[length - 1] = 0;
			}
			deleteTimer = 0;
		}
	}
}

void Asteroids_GameOver_Restart()
{
	Asteroids_Final_Boss_Reset();
	CP_Engine_SetNextGameState(Asteroids_Init, Asteroids_Update, Asteroids_Exit);
}

void Asteroids_GameOver_Quit()
{
	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
}

void Asteroids_GameOver_Update(void)
{
	deleteTimer += CP_System_GetDt();
	Asteroids_GameOver_CheckInput();

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	CP_Settings_TextSize(40.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("PLAYER NAME:", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.25f);

	CP_Settings_TextSize(50.0f);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
	//CP_Graphics_DrawRect((float)WIN_WIDTH / 3 - 5.0f, (float)WIN_HEIGHT * 0.28f, 50.0f* 13, 50);
	Asteroids_GameOver_Draw_Player_TextBar();
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	CP_Font_DrawText(CURRENT_SCORE.name, (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.325f);

	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("GAME OVER", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.1f);
	Asteroids_GameOver_Display_Score();
	
	Asteroids_Button_Update(&btnRestart);
	Asteroids_Button_Update(&btnQuit);
}

//BRYAN
void Asteroids_GameOver_Init_Score(void)
{
	sprintf_s(str_time_score, 20, "Time: %.2fs", CURRENT_SCORE.time_score);
	sprintf_s(str_kill_score, 20, "Destroyed: %d", CURRENT_SCORE.enemy_kill_score);
}

void Asteroids_GameOver_Display_Score(void)
{
	CP_Settings_TextSize(NAME_TEXT_SIZE);
	CP_Font_DrawText(str_time_score, (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.4f);
	CP_Font_DrawText(str_kill_score, (float)WIN_WIDTH / 2, (float)WIN_HEIGHT * 0.5f);
}

void Asteroids_GameOver_Exit(void)
{
	if (scoreSaved == false)
	{
		scoreSaved = true;
		Asteroids_Leaderboard_Insert_Score(CURRENT_SCORE);
	}
	Asteroids_Audio_Manager_Exit();
}

void Asteroids_GameOver_Draw_Player_TextBar(void)
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
	float length = (float)strlen(CURRENT_SCORE.name);
	float width = length * NAME_TEXT_SIZE / 2;
	CP_Graphics_DrawRect((float)WIN_WIDTH / 2 - width /2, (float)WIN_HEIGHT * 0.325f - 25, width, 50);
}