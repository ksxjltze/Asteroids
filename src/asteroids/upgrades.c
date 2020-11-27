#include "constants.h"
#include "upgrades.h"
#include "file_manager.h"

static Upgrade upgrades[NUM_UPGRADES];

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
	Asteroids_Upgrades_Create_Upgrade(FUEL_CAPACITY, ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST, "Fuel Capacity");
	Asteroids_Upgrades_Create_Upgrade(MAX_HEALTH, ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_COST, "Max Health");
	Asteroids_Upgrades_Create_Upgrade(BULLET_DMG, ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_COST, "Bullet Damage");
	Asteroids_Upgrades_Create_Upgrade(MOVE_SPEED, ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_COST, "Movement Speed");
	Asteroids_Upgrades_Create_Upgrade(FIRE_RATE, ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_COST, "Fire Rate");
}

void Asteroids_Upgrades_Create_Upgrade(unsigned int id, int cost, const char* name)
{
	Upgrade upgrade = Asteroids_Upgrades_Get_Upgrade(id);
	if (upgrade.id == NONE)
	{
		upgrade = Asteroids_Upgrades_Initialize_Upgrade(id, cost, name);
		Asteroids_Upgrades_Add_Upgrade(upgrade);
	}
}

Upgrade Asteroids_Upgrades_Initialize_Upgrade(unsigned int id, int cost, const char* name)
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

Upgrade* Asteroids_Upgrades_Get_All_Upgrades()
{
	return upgrades;
}

int Asteroids_Upgrades_Get_Upgrade_Count()
{
	int counter = 0;
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id != NONE)
		{
			counter++;
		}
	}
	return counter;
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

void Asteroids_Upgrades_Create_File(void)
{
	FILE* upgradesFile = Asteroids_Open_File("./Assets/upgrades.data", "w");
	if (upgradesFile)
	{
		Asteroids_Close_File(upgradesFile);
		Asteroids_Upgrades_Save_All_To_File();
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
			fprintf_s(upgradesFile, "%u,%d,%0.3u\n", upgrade.id, upgrade.cost, upgrade.level);
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
	else
	{
		Asteroids_Upgrades_Create_File();
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
	case BULLET_DMG:
		upgrade->name = "Bullet Damage";
		break;
	case MOVE_SPEED:
		upgrade->name = "Speed";
		break;
	case FIRE_RATE:
		upgrade->name = "Fire Rate";
	default:
		break;
	}
}