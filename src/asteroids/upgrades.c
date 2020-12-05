//---------------------------------------------------------
// file:	upgrades.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Upgrades Manager source file.
//			Handles initialization, saving, loading and updating
//			of player upgrades.
//			Provides an interface for getting a specific upgrade,
//			leveling/activating an upgrade and applying upgrades to the player.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------


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
		upgrades[i].prerequisite = NONE;
		upgrades[i].hasLevel = false;
		upgrades[i].max_level = 999;
	}

	Asteroids_Upgrades_Read_From_File();
	Asteroids_Upgrades_Create_Upgrade(FUEL_CAPACITY, ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST, "Fuel Capacity");
	Asteroids_Upgrades_Create_Upgrade(MAX_HEALTH, ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_COST, "Max Health");
	Asteroids_Upgrades_Create_Upgrade(BULLET_DMG, ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_COST, "Bullet Damage");
	Asteroids_Upgrades_Create_Upgrade(MOVE_SPEED, ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_COST, "Movement Speed");
	Asteroids_Upgrades_Create_Upgrade(FIRE_RATE, ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_COST, "Fire Rate");
	Asteroids_Upgrades_Create_Upgrade(PROJECTILE_SPEED, ASTEROIDS_UPGRADES_PROJECTILE_SPEED_UPGRADE_COST, "Projectile Speed");

	Asteroids_Upgrades_Create_Upgrade(PIERCING, ASTEROIDS_UPGRADES_PIERCING_PROJECTILES_UPGRADE_COST, "Piercing Projectiles");
	Asteroids_Upgrades_Upgrade_Disable_Levels(PIERCING);

	Asteroids_Upgrades_Create_Upgrade(MULTISHOT, ASTEROIDS_UPGRADES_MULTISHOT_UPGRADE_COST, "Multishot");
	Asteroids_Upgrades_Upgrade_Set_Max_Level(MULTISHOT, (int)(360 / ASTEROIDS_UPGRADES_MULTISHOT_ANGLE));

	Asteroids_Upgrades_Create_Upgrade(HOMING, ASTEROIDS_UPGRADES_HOMING_PROJECTILES_UPGRADE_COST, "Homing Special Attack");
	Asteroids_Upgrades_Upgrade_Disable_Levels(HOMING);

	Asteroids_Upgrades_Create_Upgrade(SWARM, ASTEROIDS_UPGRADES_SWARM_PROJECTILES_UPGRADE_COST, "Homing Swarm");
	Asteroids_Upgrades_Upgrade_Disable_Levels(SWARM);
	Asteroids_Upgrades_Upgrade_Set_Prerequisite(SWARM, HOMING);
}

void Asteroids_Upgrades_Upgrade_Set_Prerequisite(unsigned int upgrade_id, unsigned int prerequisite_id)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == upgrade_id)
		{
			upgrades[i].prerequisite = prerequisite_id;
		}
	}
}

void Asteroids_Upgrades_Upgrade_Set_Max_Level(unsigned int id, unsigned int level)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == id)
		{
			upgrades[i].max_level = level;
		}
	}
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

void Asteroids_Upgrades_Upgrade_Disable_Levels(unsigned int id)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == id)
		{
			upgrades[i].hasLevel = false;
			if (upgrades[i].level > 0)
				upgrades[i].activated = true;
			else
				upgrades[i].activated = false;
		}
	}
}

Upgrade Asteroids_Upgrades_Initialize_Upgrade(unsigned int id, int cost, const char* name)
{
	Upgrade upgrade;
	upgrade.id = id;
	upgrade.cost = cost;
	upgrade.name = name;
	upgrade.level = 0;
	upgrade.hasLevel = true;
	upgrade.prerequisite = NONE;
	upgrade.activated = false;
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
	Upgrade upgrade = Asteroids_Upgrades_Get_Upgrade_Empty();

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

bool Asteroids_Upgrade_Check_Prerequisite_Status(unsigned int id)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id != NONE)
		{
			if (upgrades[i].level > 0)
			{
				return true;
			}
		}
	}
	return false;
}

void Asteroids_Upgrade_Add_Level(unsigned int id)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == id)
		{
			if (upgrades[i].id > upgrades[i].max_level)
			{
				printf("Upgrade %s has reached the max level.\n", upgrades[i].name);
				return;
			}

			if (!upgrades[i].hasLevel)
			{
				printf("Upgrade %s has no levels.\n", upgrades[i].name);
				return;
			}

			upgrades[i].level++;
			printf("%s is now level %u\n", upgrades[i].name, upgrades[i].level);
			return;
		}
	}
}

void Asteroids_Upgrades_Upgrade_Enable(unsigned int id)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id == id)
		{
			if (upgrades[i].activated == false)
			{
				upgrades[i].activated = true;
				upgrades[i].level = 1;
			}

			printf("%s has been enabled\n", upgrades[i].name);
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

Upgrade Asteroids_Upgrades_Get_Upgrade_Empty()
{
	Upgrade upgrade;
	upgrade.id = NONE;
	upgrade.cost = 0;
	upgrade.level = 0;
	upgrade.name = "NONE";
	upgrade.hasLevel = true;
	upgrade.activated = false;
	return upgrade;
}

void Asteroids_Upgrades_Save_All_To_File(void)
{
	FILE* upgradesFile = Asteroids_Open_File("./Assets/upgrades.data", "r+");
	if (upgradesFile)
	{
		for (int i = 0; i < NUM_UPGRADES; i++)
		{
			Upgrade upgrade = Asteroids_Upgrades_Get_Upgrade_Empty();

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
			upgrade.prerequisite = NONE;
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
		break;
	case PROJECTILE_SPEED:
		upgrade->name = "Projectile Speed";
		break;
	case PIERCING:
		upgrade->name = "Piercing Projectiles";
		break;
	case MULTISHOT:
		upgrade->name = "Multishot";
		break;
	case HOMING:
		upgrade->name = "Homing Special Attack";
		break;
	case SWARM:
		upgrade->name = "Homing Swarm";
		break;
	default:
		break;
	}
}

int Asteroids_Upgrades_Reset_Upgrades(void)
{
	int refund = 0;
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (upgrades[i].id != NONE)
		{
			if (upgrades[i].hasLevel)
			{
				if (upgrades[i].level > 0)
				{
					refund += upgrades[i].level * upgrades[i].cost;
					upgrades[i].level = 0;
				}
			}
			else if (upgrades[i].activated)
			{
				refund += upgrades[i].cost;
				upgrades[i].activated = false;
				upgrades[i].level = 0;
			}
		}
	}
	Asteroids_Upgrades_Save_All_To_File();
	return refund;
}

void Asteroids_Upgrades_Apply_Upgrades(Player* player)
{
	Upgrade fuelCapacity = Asteroids_Upgrades_Get_Upgrade(FUEL_CAPACITY);
	Upgrade maxHealth = Asteroids_Upgrades_Get_Upgrade(MAX_HEALTH);
	Upgrade bulletDmg = Asteroids_Upgrades_Get_Upgrade(BULLET_DMG);
	Upgrade moveSpeed = Asteroids_Upgrades_Get_Upgrade(MOVE_SPEED);
	Upgrade fireRate = Asteroids_Upgrades_Get_Upgrade(FIRE_RATE);
	Upgrade projectileSpeed = Asteroids_Upgrades_Get_Upgrade(PROJECTILE_SPEED);
	Upgrade piercing = Asteroids_Upgrades_Get_Upgrade(PIERCING);
	Upgrade multishot = Asteroids_Upgrades_Get_Upgrade(MULTISHOT);
	Upgrade homing = Asteroids_Upgrades_Get_Upgrade(HOMING);

	if (fuelCapacity.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_FUEL_UPGRADE_AMOUNT * fuelCapacity.level;
		player->engine.fuel.max += upgrade;
		player->engine.fuel.current = player->engine.fuel.max;

		if (fuelCapacity.level > 0)
		{
			printf("Upgrade: Fuel Capacity increased by %f.\n", upgrade);
			printf("Fuel Capacity: %f\n", player->engine.fuel.max);
		}
	}

	if (maxHealth.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_MAX_HEALTH_UPGRADE_AMOUNT * maxHealth.level;
		player->hp.max += upgrade;
		player->hp.current = player->hp.max;

		if (maxHealth.level > 0)
		{
			printf("Upgrade: Max Health increased by %f.\n", upgrade);
			printf("Max Health: %f\n", player->hp.max);
		}
	}

	if (bulletDmg.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_BULLET_DAMAGE_UPGRADE_AMOUNT * bulletDmg.level;
		player->weapon.damage += upgrade;

		if (bulletDmg.level > 0)
		{
			printf("Upgrade: Bullet Damage increased by %f.\n", upgrade);
			printf("Bullet Damage: %f\n", player->weapon.damage);
		}
	}

	if (moveSpeed.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_MOVEMENT_SPEED_UPGRADE_AMOUNT * moveSpeed.level;
		player->speed += upgrade;

		if (moveSpeed.level > 0)
		{
			printf("Upgrade: Speed increased by %f.\n", upgrade);
			printf("Speed: %f\n", player->speed);
		}
	}

	if (fireRate.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_FIRE_RATE_UPGRADE_AMOUNT * fireRate.level;
		player->weapon.fire_rate += upgrade;

		if (moveSpeed.level > 0)
		{
			printf("Upgrade: Fire Rate increased by %f.\n", upgrade);
			printf("Speed: %f\n", player->weapon.fire_rate);
		}
	}

	if (projectileSpeed.id != NONE)
	{
		float upgrade = ASTEROIDS_UPGRADES_PROJECTILE_SPEED_UPGRADE_AMOUNT * projectileSpeed.level;
		player->weapon.projectile_speed += upgrade;

		if (projectileSpeed.level > 0)
		{
			printf("Upgrade: Projectile Speed increased by %f.\n", upgrade);
			printf("Speed: %f\n", player->weapon.projectile_speed);
		}
	}

	if (piercing.id != NONE)
	{
		if (piercing.activated)
		{
			player->weapon.isPiercing = true;
			printf("Upgrade: Piercing Projectiles enabled.\n");
		}
	}

	if (multishot.id != NONE)
	{
		int upgrade = multishot.level;
		player->weapon.projectile_count += upgrade;

		if (multishot.level > 0)
		{
			printf("Upgrade: Projectile Count increased by %d.\n", upgrade);
			printf("Projectile Count: %d\n", player->weapon.projectile_count);
		}
	}

	if (homing.id != NONE)
	{
		if (homing.activated)
		{
			player->weapon.special.homing = true;
			printf("Upgrade: Homing Special Attack enabled.\n");
		}
	}

}
