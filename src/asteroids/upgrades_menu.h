#pragma once
#include "upgrades.h"
#include "button.h"

typedef struct UpgradeMenuItems
{
	Upgrade upgrade;
	const char* costText;
	const char* levelText;
	Button btnBuy;
	CP_Vector pos;

}UpgradeMenuItem;

void Asteroids_Upgrades_Menu_Init(void);
void Asteroids_Upgrades_Menu_Update(void);
void Asteroids_Upgrades_Menu_Draw(void);
UpgradeMenuItem Asteroids_Upgrades_Menu_Init_Upgrade_Info(Upgrade upgrade, CP_Vector pos, void(*callback)());
void Asteroids_Upgrades_Menu_Display_Upgrade_Info(UpgradeMenuItem menuItem);
void Asteroids_Upgrades_Menu_Update_Upgrade_Info(UpgradeMenuItem* menuItem, unsigned int level);
void Asteroids_Upgrades_Menu_Upgrade_Add_Level(void* upgradePtr);