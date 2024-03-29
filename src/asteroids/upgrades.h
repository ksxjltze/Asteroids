//---------------------------------------------------------
// file:	upgrades.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Upgrades Manager header file.
//			Handles initialization, saving, loading and updating
//			of player upgrades.
//			Provides an interface for getting a specific upgrade,
//			leveling/activating an upgrade and applying upgrades to the player.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <stdbool.h>
#include "player.h"
#define NUM_UPGRADES 12

enum UpgradeType { NONE, FUEL_CAPACITY, MAX_HEALTH, BULLET_DMG, MOVE_SPEED, FIRE_RATE, PROJECTILE_SPEED, PIERCING, MULTISHOT, HOMING, SWARM};
typedef struct Upgrades
{
	const char* name;
	int cost;
	unsigned int id;
	unsigned int level;
	unsigned int max_level;
	unsigned int prerequisite;
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
bool Asteroids_Upgrade_Check_Prerequisite_Status(unsigned int id);
void Asteroids_Upgrade_Add_Level(unsigned int id);
void Asteroids_Upgrades_Upgrade_Enable(unsigned int id);
void Asteroids_Upgrades_Create_File(void);
void Asteroids_Upgrades_Save_All_To_File(void);
void Asteroids_Upgrades_Read_From_File(void);
void Asteroids_Upgrades_Set_Upgrade_Name(Upgrade* upgrade);
int Asteroids_Upgrades_Reset_Upgrades(void);
void Asteroids_Upgrades_Apply_Upgrades(Player* player);
void Asteroids_Upgrades_Upgrade_Set_Prerequisite(unsigned int upgrade_id, unsigned int prerequisite_id);
void Asteroids_Upgrades_Upgrade_Set_Max_Level(unsigned int id, unsigned int level);

//DEMO
void Asteroids_Upgrades_STRONK(void);