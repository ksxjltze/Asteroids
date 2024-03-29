#pragma once
//---------------------------------------------------------
// file:	score.h
// author:	Bryan Koh Yan Wei
//
// email:	yanweibryan.koh@digipen.edu
//
// brief:	Calculates the timed score and kill score.
//			Draws the scores onto the screen.
//			Contains variable for the playthrough which is used on the leaderboard.
//			
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include <stdio.h>

#define NAME_MAX_SIZE 20

typedef struct Scores
{
	CP_Image Asteroid_Killed_Sprite;
	CP_Image Time_Score_Sprite;
	float time_score;
	int enemy_kill_score;
	int killCountTracker;
	int difficulty_option;
	int stage;
	unsigned int id;
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
