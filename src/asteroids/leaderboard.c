#include "leaderboard.h"
#include "score.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "file_manager.h"

struct Highscore
{
	struct Scores score;
	bool isHighscore;

}TOP_HIGHSCORE;

Score* highscores;
static size_t highscore_count;

void Asteroids_Leaderboard_Init()
{
	TOP_HIGHSCORE.isHighscore = false;
	TOP_HIGHSCORE.score.enemy_kill_score = 0;
	TOP_HIGHSCORE.score.time_score = 0;

	highscore_count = 0;
	Asteroids_Leaderboard_ReadScores();

	//if (TOP_HIGHSCORE.isHighscore)
	//{
	//	highscores = malloc(sizeof(highscores));
	//	if (highscores)
	//	{
	//		*highscores = TOP_HIGHSCORE.score;

	//	}
	//}
	//if (!TOP_HIGHSCORE.isHighscore)
	//{
	//	TOP_HIGHSCORE.score.enemy_kill_score = CURRENT_SCORE.enemy_kill_score;
	//	TOP_HIGHSCORE.score.time_score = CURRENT_SCORE.time_score;

	//	if (TOP_HIGHSCORE.score.enemy_kill_score > 0 && TOP_HIGHSCORE.score.time_score > 0)
	//	{
	//		TOP_HIGHSCORE.isHighscore = true;
	//	}
	//}
}

void Asteroids_Leaderboard_Update()
{
	for (size_t i = 0; i < highscore_count; i++)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText(highscores[highscore_count].name, (float)i * 100, 100);
	}
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
	FILE* scoresFile = Asteroids_Open_File("./Assets/scores.data", "r");
	if (scoresFile)
	{
		while (1)
		{
			if (feof(scoresFile))
				return;

			Score* temp = realloc(highscores, highscore_count + 1);
			if (temp)
			{
				highscores = temp;
				Score score;
				score.time_score = 0;
				score.enemy_kill_score = 0;
				memset(score.name, 0, NAME_MAX_SIZE);

				int values_read = fscanf_s(scoresFile, "%s,%d,%f", score.name, NAME_MAX_SIZE, &score.enemy_kill_score, &score.time_score);
				//int values_read = fscanf_s(scoresFile, "%s,", score.name, NAME_MAX_SIZE);
				printf("filePos: %d\n", ftell(scoresFile));
				if (values_read == 1)
				{
					highscores[highscore_count] = score;
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

}

void Asteroids_Leaderboard_WriteScores()
{

}