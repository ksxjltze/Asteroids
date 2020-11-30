#include "leaderboard.h"
#include "score.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "file_manager.h"

const char* filePath = "./Assets/scores.data";

Score* highscores;
static size_t highscore_count;

void Asteroids_Leaderboard_Init()
{
	highscore_count = 0;
	Asteroids_Leaderboard_ReadScores();
	Asteroids_Leaderboard_WriteScores();
}

void Asteroids_Leaderboard_Update()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(30.0f);

	CP_Font_DrawText("Name", 100, 50);
	CP_Font_DrawText("Kills", 200, 50);
	CP_Font_DrawText("Time", 300, 50);

	for (size_t i = 0; i < highscore_count; i++)
	{
		CP_Vector pos = CP_Vector_Set(103, ((float)i + 1) * 50 + 40);
		CP_Font_DrawText(highscores[i].name, pos.x, pos.y);

		char killText[100];
		sprintf_s(killText, 100, "%d", highscores[i].enemy_kill_score);
		char timeText[100];
		sprintf_s(timeText, 100, "%f", highscores[i].time_score);

		CP_Font_DrawText(killText, pos.x + 100, pos.y);
		CP_Font_DrawText(timeText, pos.x + 200, pos.y);
	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BASELINE);
}

void Asteroids_Leaderboard_Exit()
{
	if (highscores)
	{
		free(highscores);
	}
}

void Asteroids_Leaderboard_ReadScores()
{
	FILE* scoresFile = Asteroids_Open_File(filePath, "r");
	if (scoresFile)
	{
		while (1)
		{
			if (feof(scoresFile))
				break;

			Score* temp = realloc(highscores, sizeof(Score) * (highscore_count + 1));
			if (temp)
			{
				highscores = temp;
				Score score;
				score.time_score = 0;
				score.enemy_kill_score = 0;
				memset(score.name, 0, NAME_MAX_SIZE);

				int values_read = fscanf_s(scoresFile, "%s %d,%f", score.name, NAME_MAX_SIZE, &score.enemy_kill_score, &score.time_score);
				if (values_read == 3)
				{
					highscores[highscore_count] = score;
					highscore_count++;
					printf("Highscore added.\n");
				}
				else
				{
					printf("Error: Failed to read highscore.\n");
				}

			}
			else
				printf("Error: Failed to Reallocate memory for highscores.");
		}
		Asteroids_Close_File(scoresFile);
	}
	else
		Asteroids_Leaderboard_WriteScores();

}

void Asteroids_Leaderboard_WriteScores()
{
	FILE* scoresFile = Asteroids_Open_File(filePath, "w");
	if (scoresFile)
	{
		for (size_t i = 0; i < highscore_count; i++)
		{
			fprintf_s(scoresFile, "%s %d,%f\n", highscores[i].name, highscores[i].enemy_kill_score, highscores[i].time_score);
		}
		Asteroids_Close_File(scoresFile);
	}
}

void Asteroids_Leaderboard_Insert_Score(Score score)
{
	Asteroids_Leaderboard_ReadScores();
	qsort_s(highscores, highscore_count, sizeof(Score), Asteroids_Leaderboard_Compare_Highscores, &score);
	FILE* scoresFile = Asteroids_Open_File(filePath, "r+");
	if (scoresFile)
	{
		for (size_t i = 0; i < highscore_count; i++)
		{
			
		}
		Asteroids_Close_File(scoresFile);
	}
}

int Asteroids_Leaderboard_Compare_Highscores(const void* left, const void* right)
{

}