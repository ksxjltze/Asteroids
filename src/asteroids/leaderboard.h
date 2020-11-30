#pragma once
#include "score.h"

void Asteroids_Leaderboard_Init();
void Asteroids_Leaderboard_Update();
void Asteroids_Leaderboard_Exit();

void Asteroids_Leaderboard_Insert_Score(Score score);
Score* Asteroids_Leaderboard_GetScores();
int Asteroids_Leaderboard_Compare_Highscores(void* context, const void* lhs, const void* rhs);
void Asteroids_Leaderboard_ReadScores();
void Asteroids_Leaderboard_WriteScores();