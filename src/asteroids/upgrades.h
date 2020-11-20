#pragma once

enum UpgradeType {NONE, FUEL_CAPACITY};

typedef struct Upgrades
{
	const char* name;
	unsigned int id;
	unsigned int level;
}Upgrade;

void Asteroids_Upgrades_Init(void);
void Asteroids_Upgrades_Add_Upgrade(Upgrade upgrade);
Upgrade Asteroids_Upgrades_Get_Upgrade(unsigned int id);