#include "upgrades.h"
#include <stdio.h>

#define NUM_UPGRADES 10
Upgrade upgrades[NUM_UPGRADES];

void Asteroids_Upgrades_Init(void)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		upgrades[i].id = NONE;
		upgrades[i].level = 0;
		upgrades[i].name = "NONE";
	}

	Upgrade upgrade_FuelCapacity;
	upgrade_FuelCapacity.id = FUEL_CAPACITY;
	upgrade_FuelCapacity.name = "Fuel Capacity";
	upgrade_FuelCapacity.level = 0;
	Asteroids_Upgrades_Add_Upgrade(upgrade_FuelCapacity);
}

void Asteroids_Upgrades_Add_Upgrade(Upgrade upgrade)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == upgrade.id)
		{
			printf("Upgrade %s already exists.\n", upgrade.name);
			return;
		}
	}
	
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == NONE)
		{
			upgrades[i] = upgrade;
			printf("Upgrade %s added.\n", upgrade.name);
			return;
		}
	}

}

Upgrade Asteroids_Upgrades_Get_Upgrade(unsigned int id)
{
	Upgrade upgrade;
	upgrade.id = NONE;
	upgrade.name = "NONE";
	upgrade.level = 0;

	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == id)
		{
			upgrade = upgrades[i];
		}
	}
	return upgrade;
}

void Asteroids_Upgrade_Add_Level(unsigned int id)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == id)
		{
			upgrades[i].level++;
			printf("%s is now level %u\n", upgrades[i].name, upgrades[i].level);
			return;
		}
	}
}