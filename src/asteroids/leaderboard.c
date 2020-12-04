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

#define SCORE_VARIABLES_COUNT 5
const char* filePath = "./Assets/scores.data";
CP_Vector cameraPos;

Score* highscores;
static size_t highscore_count;
float offsets[SCORE_VARIABLES_COUNT] = { 100, 250, 400, 550, 750 };
char labels[SCORE_VARIABLES_COUNT][20] = { "Name", "Kills", "Time", "Difficulty", "Score" };

void Asteroids_Leaderboard_Init()
{
	highscores = NULL;
	highscore_count = 0;
	Asteroids_Leaderboard_ReadScores();
	cameraPos = CP_Vector_Zero();
}

void Asteroids_Leaderboard_Update()
{
	Asteroids_Leaderboard_Check_Input();

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(30.0f);

	for (int i = 0; i < SCORE_VARIABLES_COUNT; i++)
	{
		CP_Vector pos = CP_Vector_Set(offsets[i], 50);
		pos = CP_Vector_MatrixMultiply(CP_Matrix_Translate(cameraPos), pos);
		CP_Font_DrawText(labels[i], pos.x, pos.y);
	}

	for (size_t i = 0; i < highscore_count; i++)
	{
		CP_Vector pos = CP_Vector_Set(103, ((float)i + 1) * 50 + 40);
		pos = CP_Vector_MatrixMultiply(CP_Matrix_Translate(cameraPos), pos);

		char scoreStrings[SCORE_VARIABLES_COUNT][100];
		for (int j = 0; j < SCORE_VARIABLES_COUNT; j++)
		{
			memset(scoreStrings[j], 0, 100);
		}

		strcpy_s(scoreStrings[0], NAME_MAX_SIZE, highscores[i].name);
		sprintf_s(scoreStrings[1], 100, "%d", highscores[i].enemy_kill_score);
		sprintf_s(scoreStrings[2], 100, "%.2fs", highscores[i].time_score);
		strcpy_s(scoreStrings[3], 20, Asteroids_Leaderboard_Evaluate_Difficulty(highscores[i].difficulty));
		sprintf_s(scoreStrings[4], 100, "%.d", Asteroids_Leaderboard_Evaluate_Score(highscores[i]));

		for (int j = 0; j < SCORE_VARIABLES_COUNT; j++)
		{
			CP_Font_DrawText(scoreStrings[j], offsets[j], pos.y);
		}

	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void Asteroids_Leaderboard_Check_Input()
{
	if (CP_Input_MouseWheel() != 0)
	{
		cameraPos.y += CP_Input_MouseWheel() * 100;
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
				score.difficulty = 0;
				memset(score.name, 0, NAME_MAX_SIZE);

				int values_read = fscanf_s(scoresFile, "%s %d,%f,%d", score.name, NAME_MAX_SIZE, &score.enemy_kill_score, &score.time_score, &score.difficulty);
				if (values_read == 4)
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
			fprintf_s(scoresFile, "%s %d,%f,%d\n", highscores[i].name, highscores[i].enemy_kill_score, highscores[i].time_score, highscores[i].difficulty);
		}
		Asteroids_Close_File(scoresFile);
	}
}

int Asteroids_Leaderboard_Evaluate_Score(Score score)
{
	return (int)((score.enemy_kill_score + score.time_score) * score.difficulty);
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