#include "upgrades.h"
#include <stdio.h>
#include "constants.h"
#include "file_manager.h"

#define NUM_UPGRADES 10
Upgrade upgrades[NUM_UPGRADES];

void Asteroids_Upgrades_Init(void)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		upgrades[i].id = NONE;
		upgrades[i].cost = 0;
		upgrades[i].level = 0;
		upgrades[i].name = "NONE";
	}

	Upgrade upgrade_FuelCapacity = Asteroids_Upgrades_Create_Upgrade(FUEL_CAPACITY, ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST, "Fuel Capacity");
	upgrade_FuelCapacity = Asteroids_Upgrades_Read_From_File();
	Asteroids_Upgrades_Add_Upgrade(upgrade_FuelCapacity);

}

Upgrade Asteroids_Upgrades_Create_Upgrade(unsigned int id, int cost, const char* name)
{
	Upgrade upgrade;
	upgrade.id = id;
	upgrade.cost = cost;
	upgrade.name = name;
	upgrade.level = 0;
	return upgrade;
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
	upgrade.cost = 0;
	upgrade.level = 0;
	upgrade.name = "NONE";

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

void Asteroids_Upgrades_Save_To_File(Upgrade upgrade)
{
	FILE* upgradesFile = Asteroids_Open_File("./Assets/upgrades.data", "w");
	if (upgradesFile)
	{
		fprintf_s(upgradesFile, "%u,%u", upgrade.id, upgrade.level);
		Asteroids_Close_File(upgradesFile);
	}
}

Upgrade Asteroids_Upgrades_Read_From_File(void)
{
	Upgrade upgrade;
	upgrade.id = NONE;
	upgrade.cost = 0;
	upgrade.level = 0;
	upgrade.name = "NONE";

	FILE* upgradesFile = Asteroids_Open_File("./Assets/upgrades.data", "r");
	if (upgradesFile)
	{
		int read = fscanf_s(upgradesFile, "%u,%u", &upgrade.id, &upgrade.level);
		printf("Read %d values from file %s.", read, "./Assets/upgrades.data");
		Asteroids_Close_File(upgradesFile);
	}

	return upgrade;
}