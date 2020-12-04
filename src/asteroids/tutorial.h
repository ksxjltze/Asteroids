#pragma once
#include "cprocessing.h"

void Asteroids_Tutorial_Init();
void Asteroids_Tutorial_Update();
void Asteroids_Tutorial_Exit();

void Asteroids_Tutorial_State_Update();
void Asteroids_Tutorial_State_Move_Tutorial();
void Asteroids_Tutorial_DrawText(CP_Vector pos, const char* text);
