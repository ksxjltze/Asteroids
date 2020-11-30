#pragma once
#include "cprocessing.h"
#include <stdio.h>

#define NAME_MAX_SIZE 30

typedef struct Scores
{
	CP_Image Asteroid_Killed_Sprite;
	CP_Image Time_Score_Sprite;
	float time_score;
	int enemy_kill_score;
	char name[NAME_MAX_SIZE];
} Score;

Score CURRENT_SCORE;

//INITIALIZE VARIABLES
void Asteroids_Init_Score(void);

// DRAW SCORE TO SCREEN
void Asteroids_Draw_Scores(void);

// SCORE MANAGERS
void Asteroids_EnemyKill_Score_Manager(void);
void Asteroids_Time_Score_Manager(void);

void Asteroids_Pause_Timer(void);
void Asteroids_Resume_Timer(void);
