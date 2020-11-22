#include "currency.h"
#include <stdio.h>
#include "file_manager.h"

static int currentCredits = 0;

void Asteroids_Currency_Init(void)
{
	if (currentCredits == 0)
		Asteroids_Currency_Get_From_File();
	else
		Asteroids_Currency_Write_To_File();
	printf("Credits: %d\n", currentCredits);
}

void Asteroids_Currency_Add(int amount)
{
	currentCredits += amount;
	printf("Credits: %d\n", currentCredits);
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
		Asteroids_Currency_Write_To_File();
	}
	return false;
}

void Asteroids_Currency_Write_To_File()
{
	FILE* creditsFile = Asteroids_Open_File("./Assets/credits.data", "w");
	fprintf(creditsFile, "%d", currentCredits);
	Asteroids_Close_File(creditsFile);
}
