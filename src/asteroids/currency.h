//---------------------------------------------------------
// file:	currency.h
// author:	Lee Jia Keat, Bryan Koh Yan Wei
// email:	l.jiakeat@digipen.edu
//
// brief:	Currency Manager header file.
//			Reads and Writes currency data (credits)
//			from a specific text file.
//			Provides an interface for updating
//			(Adding and Subtracting) currency balance.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <stdbool.h>

//JIA KEAT
void Asteroids_Currency_Init(void);
void Asteroids_Currency_Add(int amount);
int Asteroids_Currency_Get_Balance();
bool Asteroids_Currency_Deduct_Balance(int amount);
bool Asteroids_Currency_Get_From_File();
void Asteroids_Currency_Write_To_File();

//BRYAN
void Asteroids_Currency_Earning_Manager(void);