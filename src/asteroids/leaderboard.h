#pragma once
#include "cprocessing.h"
#include "menu.h"
#include <stdio.h>
#include "globals.h"
#include <string.h>
#include <stdbool.h>
#include "player.h"

struct LeaderBoard
{
	CP_Color text_color;
	const char* text;
	float x, y;
}Leaderboard_Variables;


typedef struct Leaders
{
	char name[21];
	int score;
} Leader;

struct Counters
{
	int leaders_count;
	int name_length;
}counter;

void Init_LeaderBoard(void);
void Update_LeaderBoard(void);
void Exit_LeaderBoard(void);

void Read_Leaderboard_Data(void);
void Write_Leaderboard_Data(void);
void Check_If_Leader(void);
void LeaderBoard_ReadInput();
void Draw_LeaderBoard(void);
void Load_Main_Menu(void);
void Draw_LeaderBoard(void);

void LeaderBoard_Display_PlayerName();
void Sort_Data(int LeaderBoard_Scores[], int n);
void Player_Is_Leader(void);