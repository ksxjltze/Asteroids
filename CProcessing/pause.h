#pragma once
#include <stdbool.h>
#include "cprocessing.h"
#include "utility.h"
#include "constants.h"

void Asteroids_Pause_Init();
void Asteroids_Pause_CheckInput();
void Asteroids_Pause_Update();

void Asteroids_Pause_Toggle();
void Asteroids_Pause_DisplayMenu();
bool Asteroids_Pause_GetStatus();