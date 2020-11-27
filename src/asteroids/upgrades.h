#pragma once
#include <stdbool.h>
#include "player.h"
#define NUM_UPGRADES 10

enum UpgradeType { NONE, FUEL_CAPACITY, MAX_HEALTH, BULLET_DMG, MOVE_SPEED, FIRE_RATE, PROJECTILE_SPEED, PIERCING};
typedef struct Upgrades
{
	const char* name;
	int cost;
	unsigned int id;
	unsigned int level;
	bool hasLevel;
	bool activated;
}Upgrade;


void Asteroids_Upgrades_Init(void);
Upgrade Asteroids_Upgrades_Initialize_Upgrade(unsigned int id, int cost, const char* name);
void Asteroids_Upgrades_Create_Upgrade(unsigned int id, int cost, const char* name);
void Asteroids_Upgrades_Upgrade_Disable_Levels(unsigned int id);
void Asteroids_Upgrades_Add_Upgrade(Upgrade upgrade);
Upgrade Asteroids_Upgrades_Get_Upgrade(unsigned int id);
Upgrade* Asteroids_Upgrades_Get_All_Upgrades();
Upgrade Asteroids_Upgrades_Get_Upgrade_Empty();
int Asteroids_Upgrades_Get_Upgrade_Count();
void Asteroids_Upgrade_Add_Level(unsigned int id);
void Asteroids_Upgrades_Upgrade_Enable(unsigned int id);
void Asteroids_Upgrades_Create_File(void);
void Asteroids_Upgrades_Save_All_To_File(void);
void Asteroids_Upgrades_Read_From_File(void);
void Asteroids_Upgrades_Set_Upgrade_Name(Upgrade* upgrade);
void Asteroids_Upgrades_Apply_Upgrades(Player* player);