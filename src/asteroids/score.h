#pragma once
#include "cprocessing.h"
#include <stdio.h>

struct Scores
{
	CP_Image Asteroid_Killed_Sprite;
	CP_Image Time_Score_Sprite;
	float time_score;
	int enemy_kill_score;
}Score;

//INITIALIZE VARIABLES
void Asteroids_Init_Score(void);

// DRAW SCORE TO SCREEN
void Asteroids_Draw_Scores(void);

// SCORE MANAGERS
void Asteroids_EnemyKill_Score_Manager(void);
void Asteroids_Time_Score_Manager(void);