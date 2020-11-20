#include "currency.h"
#include <stdio.h>
#include "file_manager.h"

static int currentCredits;

void Asteroids_Currency_Init(void)
{
	currentCredits = 0;
	Asteroids_Currency_Get_From_File();
	printf("Credits: %d\n", currentCredits);
}

void Asteroids_Currency_Add(int amount)
{
	currentCredits += amount;
}

void Asteroids_Currency_Get_From_File()
{
	FILE* creditsFile = Asteroids_Open_File("./Assets/credits.data", "r");
	if (creditsFile)
	{
		fscanf_s(creditsFile, "%d", &currentCredits);
		Asteroids_Close_File(creditsFile);
	}
	else
	{
		Asteroids_Currency_Write_To_File();
	}
}

void Asteroids_Currency_Write_To_File()
{
	FILE* creditsFile = Asteroids_Open_File("./Assets/credits.data", "w");
	fprintf(creditsFile, "%d", currentCredits);
	Asteroids_Close_File(creditsFile);
}
