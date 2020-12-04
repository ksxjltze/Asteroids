//---------------------------------------------------------
// file:	leaderboard.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Leaderboard source file. Reads and Writes data 
//			to and from a text file, dynamically allocating
//			an array of Score structs to display a leaderboard
//			of highscores.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "leaderboard.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "file_manager.h"
#include "game.h"
#include "constants.h"

#define SCORE_VARIABLES_COUNT 6
const char* filePath = "./Assets/scores.data";
CP_Vector cameraPos;

Score* highscores;
static size_t highscore_count;

static float row_width = 40;
static int row_count = 16;

float offsets[SCORE_VARIABLES_COUNT] = { 100, 350, 500, 650, 850, 1050};
char labels[SCORE_VARIABLES_COUNT][20] = { "Name", "Kills", "Time", "Difficulty", "Stage", "Score" };

void Asteroids_Leaderboard_Init()
{
	highscores = NULL;
	highscore_count = 0;
	Asteroids_Leaderboard_ReadScores();
	cameraPos = CP_Vector_Zero();
}

void Asteroids_Leaderboard_Draw_Scrollbar()
{
	CP_Vector pos = CP_Vector_Set(50, 50);
	//bar
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	float scrollbar_height = (float)WIN_HEIGHT - pos.y * 2;
	CP_Graphics_DrawRect(pos.x, pos.y, 20, scrollbar_height);

	//scroll thingy
	//printf("%.2f\n", cameraPos.y / row_width);
	printf("%.2f\n", cameraPos.y);
	//printf("%f\n", (float)highscore_count * row_width);
	pos.y += (cameraPos.y / row_width) * (scrollbar_height / (highscore_count - row_count)); 
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(pos.x, pos.y, 20, 10);
}

void Asteroids_Leaderboard_Update()
{
	Asteroids_Leaderboard_Check_Input();

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(20.0f);

	for (int i = 0; i < SCORE_VARIABLES_COUNT; i++)
	{
		CP_Vector pos = CP_Vector_Set(offsets[i], row_width);
		CP_Font_DrawText(labels[i], pos.x, pos.y);
	}

	for (size_t i = 0; i < highscore_count; i++)
	{
		CP_Vector pos = CP_Vector_Set(103, ((float)i + 1) * row_width + 40);
		pos = CP_Vector_MatrixMultiply(CP_Matrix_Translate(CP_Vector_Negate(cameraPos)), pos);

		char scoreStrings[SCORE_VARIABLES_COUNT][100];
		for (int j = 0; j < SCORE_VARIABLES_COUNT; j++)
		{
			memset(scoreStrings[j], 0, 100);
		}

		strcpy_s(scoreStrings[0], NAME_MAX_SIZE, highscores[i].name);
		sprintf_s(scoreStrings[1], 100, "%d", highscores[i].enemy_kill_score);
		sprintf_s(scoreStrings[2], 100, "%.2fs", highscores[i].time_score);
		strcpy_s(scoreStrings[3], 20, Asteroids_Leaderboard_Evaluate_Difficulty(highscores[i].difficulty_option));
		strcpy_s(scoreStrings[4], 20, Asteroids_Leaderboard_Evaluate_Difficulty(highscores[i].stage));
		sprintf_s(scoreStrings[5], 100, "%.d", Asteroids_Leaderboard_Evaluate_Score(highscores[i]));

		for (int j = 0; j < SCORE_VARIABLES_COUNT; j++)
		{
			if (pos.y <= 50)
				continue;
			CP_Font_DrawText(scoreStrings[j], offsets[j], pos.y);
		}

	}
	Asteroids_Leaderboard_Draw_Scrollbar();
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void Asteroids_Leaderboard_Check_Input()
{
	if (CP_Input_MouseWheel() != 0)
	{
		float leaderboardMaxY = highscore_count * row_width - row_count * row_width;
		cameraPos.y -= CP_Input_MouseWheel() * row_width;
		if (cameraPos.y < 0)
			cameraPos.y = 0;
		else if (cameraPos.y > leaderboardMaxY)
			cameraPos.y = leaderboardMaxY;
	}
}

char* Asteroids_Leaderboard_Evaluate_Difficulty(int difficulty)
{
	static char difficultyString[20];
	memset(difficultyString, 0, 20);
	switch (difficulty)
	{
	case 0:
		strcpy_s(difficultyString, 20, "NULL");
		break;
	case EASY:
		strcpy_s(difficultyString, 20, "EASY");
		break;	
	case NORMAL:
		strcpy_s(difficultyString, 20, "NORMAL");
		break;
	case HARD:
		strcpy_s(difficultyString, 20, "HARD");
		break;
	case INSANE:
		strcpy_s(difficultyString, 20, "INSANE");
		break;
	case IMPOSSIBLE:
		strcpy_s(difficultyString, 20, "IMPOSSIBLE");
		break;
	case PEPEGA:
		strcpy_s(difficultyString, 20, "PEPEGA");
		break;
	case BRUH:
		strcpy_s(difficultyString, 20, "BRUH");
		break;
	}

	if (difficulty > BRUH)
	{
		sprintf_s(difficultyString, 20, "BRUH + %d", difficulty - BRUH);
	}

	return difficultyString;
}

void Asteroids_Leaderboard_Exit()
{
	if (highscores)
	{
		free(highscores);
		highscores = NULL;
		highscore_count = 0;
	}
}

void Asteroids_Leaderboard_Insert_Score(Score score)
{
	Asteroids_Leaderboard_GetScores();
	Score* temp = realloc(highscores, sizeof(Score) * (highscore_count + 1));
	if (temp)
	{
		highscores[highscore_count] = score;
		highscore_count++;

		qsort_s(highscores, highscore_count, sizeof(Score), &Asteroids_Leaderboard_Compare_Highscores, NULL);
		Asteroids_Leaderboard_WriteScores();
	}
	else
		printf("Error: Failed to Reallocate memory for inserting new score.");
}

Score* Asteroids_Leaderboard_GetScores()
{
	if (!highscores)
		Asteroids_Leaderboard_ReadScores();
	return highscores;
}

void Asteroids_Leaderboard_ReadScores()
{
	FILE* scoresFile = Asteroids_Open_File(filePath, "r");
	if (scoresFile)
	{
		while (1)
		{
			Score* temp = realloc(highscores, sizeof(Score) * (highscore_count + 1));
			if (temp)
			{
				highscores = temp;
				Score score;
				score.time_score = 0;
				score.enemy_kill_score = 0;
				score.difficulty_option = 0;
				memset(score.name, 0, NAME_MAX_SIZE);

				int values_read = fscanf_s(scoresFile, "%s %d,%f,%d,%d", score.name, NAME_MAX_SIZE, &score.enemy_kill_score, &score.time_score, &score.difficulty_option, &score.stage);
				if (values_read == SCORE_VARIABLES_COUNT - 1)
				{
					highscores[highscore_count] = score;
					highscores[highscore_count].id = (int)highscore_count;
					printf("Highscore added.\n");
					highscore_count++;
				}
				else
				{
					if (feof(scoresFile))
						break;
					printf("Error: Failed to read highscore.\n");
				}

			}
			else
				printf("Error: Failed to Reallocate memory for highscores.");
		}
		Asteroids_Close_File(scoresFile);
	}
	else
	{
		Asteroids_Leaderboard_WriteScores();
		Asteroids_Leaderboard_ReadScores();
	}

}

void Asteroids_Leaderboard_WriteScores()
{
	FILE* scoresFile = Asteroids_Open_File(filePath, "w");
	if (scoresFile)
	{
		for (size_t i = 0; i < highscore_count; i++)
		{
			fprintf_s(scoresFile, "%s %d,%f,%d,%d\n", highscores[i].name, highscores[i].enemy_kill_score, highscores[i].time_score, highscores[i].difficulty_option, highscores[i].stage);
		}
		Asteroids_Close_File(scoresFile);
	}
}

int Asteroids_Leaderboard_Evaluate_Score(Score score)
{
	return (int)((score.enemy_kill_score + score.time_score) * score.difficulty_option);
}

int Asteroids_Leaderboard_Compare_Highscores(void* context, const void* lhs, const void* rhs)
{
	Score left = *(Score*)lhs;
	Score right = *(Score*)rhs;

	if (Asteroids_Leaderboard_Evaluate_Score(left) < Asteroids_Leaderboard_Evaluate_Score(right))
		return 1;
	else if (Asteroids_Leaderboard_Evaluate_Score(left) > Asteroids_Leaderboard_Evaluate_Score(right))
		return -1;
	return 0;
}