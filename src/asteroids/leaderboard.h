//---------------------------------------------------------
// file:	leaderboard.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Leaderboard header file. Reads and Writes data 
//			to and from a text file, dynamically allocating
//			an array of Score structs to display a leaderboard
//			of highscores.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

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
char* Asteroids_Leaderboard_Evaluate_Difficulty(int difficulty);
int Asteroids_Leaderboard_Evaluate_Score(Score score);