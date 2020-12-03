//---------------------------------------------------------
// file:	currency.c
// author:	Lee Jia Keat, Bryan Koh Yan Wei
// email:	l.jiakeat@digipen.edu
//
// brief:	Currency Manager source file.
//			Reads and Writes currency data (credits)
//			from a specific text file.
//			Provides an interface for updating
//			(Adding and Subtracting) currency balance.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "currency.h"
#include <stdio.h>
#include "file_manager.h"
#include "constants.h"
#include "game.h"

static int currentCredits = 0;
static float kills = 0;
static float time = 0;
static int currency_factor = 0;
static int currency = 0;

//JIA KEAT
void Asteroids_Currency_Init(void)
{
	if (currentCredits == 0)
		Asteroids_Currency_Get_From_File();
	else
		Asteroids_Currency_Write_To_File();
	printf("Credits: %d\n", currentCredits);

	currency = ASTEROIDS_ENEMY_CURRENCY_DROP_AMOUNT;
	currency_factor = ASTEROIDS_CURRENCY_EARNING_BALANCE_BASE;
}

void Asteroids_Currency_Add(int amount)
{
	currentCredits += amount;
}

int Asteroids_Currency_Get_Balance()
{
	return currentCredits;
}

bool Asteroids_Currency_Deduct_Balance(int amount)
{
	if (currentCredits - amount < 0)
	{
		printf("Not enough money.\n");
		return false;
	}

	currentCredits -= amount;
	Asteroids_Currency_Write_To_File();
	return true;
}

bool Asteroids_Currency_Get_From_File()
{
	FILE* creditsFile = Asteroids_Open_File("./Assets/credits.data", "r");
	if (creditsFile)
	{
		fscanf_s(creditsFile, "%d", &currentCredits);
		Asteroids_Close_File(creditsFile);
		return true;
	}
	else
	{
		currentCredits = ASTEROIDS_CURRENCY_STARTING_BALANCE;
		Asteroids_Currency_Write_To_File();
	}
	return false;
}

void Asteroids_Currency_Write_To_File()
{
	FILE* creditsFile = Asteroids_Open_File("./Assets/credits.data", "w");
	if (creditsFile)
	{
		fprintf(creditsFile, "%d", currentCredits);
		Asteroids_Close_File(creditsFile);
	}
}

//BRYAn
void Asteroids_Currency_Earning_Manager(void)
{
	kills += 1;
	if (kills >= 100 && currency_factor < ASTEROIDS_CURRENCY_EARNING_BALANCE_MAX)
	{
		currency_factor += 1;
		kills = 0;
	}
	// eg: 1 * 10 * 6 = 60? hm
	int earnings = ASTEROIDS_ENEMY_CURRENCY_DROP_AMOUNT * currency_factor * ASTEROIDS_GAME_DIFFICULTY;
	Asteroids_Currency_Add(earnings);
}
