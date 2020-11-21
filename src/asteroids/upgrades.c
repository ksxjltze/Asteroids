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
		if (upgrades[i].id > 0)
			continue;

		upgrades[i].id = NONE;
		upgrades[i].cost = 0;
		upgrades[i].level = 0;
		upgrades[i].name = "NONE";
	}

	Asteroids_Upgrades_Read_From_File();

	Upgrade upgrade_FuelCapacity = Asteroids_Upgrades_Get_Upgrade(FUEL_CAPACITY);
	if (upgrade_FuelCapacity.id == NONE)
	{
		upgrade_FuelCapacity = Asteroids_Upgrades_Create_Upgrade(FUEL_CAPACITY, ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST, "Fuel Capacity");
		Asteroids_Upgrades_Add_Upgrade(upgrade_FuelCapacity);
	}

	Upgrade upgrade_MaxHealth = Asteroids_Upgrades_Get_Upgrade(MAX_HEALTH);
	if (upgrade_MaxHealth.id == NONE)
	{
		upgrade_MaxHealth = Asteroids_Upgrades_Create_Upgrade(MAX_HEALTH, ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST, "Max Health");
		Asteroids_Upgrades_Add_Upgrade(upgrade_MaxHealth);
	}
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

void Asteroids_Upgrades_Save_All_To_File(void)
{
	FILE* upgradesFile = Asteroids_Open_File("./Assets/upgrades.data", "r+");
	if (upgradesFile)
	{
		for (int i = 0; i < NUM_UPGRADES; i++)
		{
			Upgrade upgrade;
			upgrade.id = NONE;
			upgrade.cost = 0;
			upgrade.level = 0;
			upgrade.name = "NONE";

			int filePos = ftell(upgradesFile);
			int read = fscanf_s(upgradesFile, "%u,%d,%u", &upgrade.id, &upgrade.cost, &upgrade.level);
			upgrade = Asteroids_Upgrades_Get_Upgrade(i + 1);

			if (upgrade.id == NONE)
				continue;

			printf("Read %d values from file %s.\n", read, "./Assets/upgrades.data");
			if (read == 3)
			{
				fseek(upgradesFile, -(ftell(upgradesFile) - filePos), SEEK_CUR);
			}
			fprintf_s(upgradesFile, "%u,%d,%u\n", upgrade.id, upgrade.cost, upgrade.level);
			fflush(upgradesFile);
		}
		Asteroids_Close_File(upgradesFile);
	}
}

void Asteroids_Upgrades_Read_From_File(void)
{
	FILE* upgradesFile = Asteroids_Open_File("./Assets/upgrades.data", "r");
	if (upgradesFile)
	{
		for (int i = 0; i < NUM_UPGRADES; i++)
		{
			Upgrade upgrade;
			upgrade.id = NONE;
			upgrade.cost = 0;
			upgrade.level = 0;
			upgrade.name = "NONE";

			int read = fscanf_s(upgradesFile, "%u,%d,%u", &upgrade.id, &upgrade.cost, &upgrade.level);
			if (read != 3)
				continue;
			printf("Read %d values from file %s.", read, "./Assets/upgrades.data");

			Asteroids_Upgrades_Set_Upgrade_Name(&upgrade);
			Asteroids_Upgrades_Add_Upgrade(upgrade);
		}
		Asteroids_Close_File(upgradesFile);
	}
}

void Asteroids_Upgrades_Set_Upgrade_Name(Upgrade* upgrade)
{
	switch (upgrade->id)
	{
	case FUEL_CAPACITY:
		upgrade->name = "Fuel Capacity";
		break;
	case MAX_HEALTH:
		upgrade->name = "Max Health";
		break;
	default:
		break;
	}
}