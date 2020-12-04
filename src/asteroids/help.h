#pragma once
#include "cprocessing.h"
#include <stdbool.h>

typedef struct Help_Screen
{
	int id;
	CP_Vector pos;
	CP_Image Image;
	bool active;
	float width, height;
}Help_screen;

void Asteroids_Help_Screen_Init(void);
void Asteroids_Help_Screen_Update(void);
void Asteroids_Help_Screen_Exit(void);

void Asteroids_Draw_Screen_Page(void);

int Asteroids_Help_Screen_CheckPageNo(void);
void Asteroids_Help_Screen_CheckInput(void);