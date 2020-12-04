//---------------------------------------------------------
// file:	user_interface.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu, 
//
// brief:	User interface header file.
//			Display the main user interface for the game.
//			i.e. Player Health, Fuel meter, etc.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "health.h"
#include "fuel.h"
#include "player.h"

void Asteroids_UI_Init();
void Asteroids_UI_Update(Player player);

void Asteroids_UI_Draw(Player player);
void Asteroids_UI_Health_HP_Draw(Health hp);
void Asteroids_UI_Fuel_Draw(Fuel fuel);
void Asteroids_UI_Display_Current_Difficulty(void);
void Asteroids_UI_Display_Difficulty_Meter(void);

