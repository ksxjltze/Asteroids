#pragma once
#include "cprocessing.h"

void Asteroids_Tutorial_Init(void);
void Asteroids_Tutorial_Update(void);
void Asteroids_Tutorial_Draw(void);
void Asteroids_Tutorial_Exit(void);

void Asteroids_Tutorial_State_Update();
void Asteroids_Tutorial_State_Move_Tutorial(void* context);
void Asteroids_Tutorial_DrawText(CP_Vector pos, const char* text);
