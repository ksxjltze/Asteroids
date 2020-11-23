#pragma once
#include "cprocessing.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "player.h"
#include "main_menu.h"
#include "constants.h"
#include "button.h"
#include "file_manager.h"
#include "score.h"

#define MAX_LEADER 5
#define MAX_INPUT_LEN 20

struct Leaderboards
{
	CP_Color text_color;
	CP_Vector pos;
	float textsize;
	const char* text;
	float player_score;
	char player_name[MAX_INPUT_LEN + 1];

}Leaderboard;

typedef struct Leader
{
	char name[MAX_INPUT_LEN + 1];
	float score;
}Leaders;

struct Counters
{
	int leaders_count;
	int name_length;
}counter;

//struct LeaderBoard
//{
//	CP_Color text_color;
//	const char* text;
//	float x, y;
//}Leaderboard_Variables;

//
//typedef struct Leaders
//{
//	char name[21];
//	int score;
//} Leader;
//

void Asteroids_Init_LeaderBoard(void);
void Asteroids_Update_LeaderBoard(void);
void Asteroids_Read_LeaderBoard_Data(void);

bool Asteroids_Check_If_Leader(void);
void Asteroids_Write_LeaderBoard_Data(void);
int Asteroids_Compare_LeaderScore(const void* first, const void* second);
void Asteroids_LeaderBoard_ReadInput(void);

void Asteroids_LeaderBoard_Draw(void);

void Asteroids_LeaderBoard_Display_PlayerName(void);