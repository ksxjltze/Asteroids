#pragma once
#include "cprocessing.h"

#define MAXPAGE 3
typedef struct creditsScreen
{
	int ID;
	CP_Vector pos;
	CP_Image page[MAXPAGE];
	float width, height;
}creditsScreen;

void Asteroids_Credits_Screen_Init(void);
void Asteroids_Credits_Screen_ButtonInit(void);
void Asteroids_Credits_Screen_Update(void);
void Asteroids_Credits_Screen_Exit(void);

void Asteroids_Credits_Screen_NextPage(void);
void Asteroids_Credits_Screen_PreviousPage(void);
void Asteroids_Credits_Screen_ExitToMenu(void);

void Asteroids_Credits_Screen_Draw(void);