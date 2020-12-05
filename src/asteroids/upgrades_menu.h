//---------------------------------------------------------
// file:	upgrades_menu.h
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Upgrades Menu header file.
//			Draws the user interface (menu) for
//			purchasing upgrades using currency (credits).
//			Displays available upgrades and credits balance/
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "upgrades.h"
#include "button.h"

#define BALANCE_BUFFER_SIZE 100
#define COST_BUFFER_SIZE 20
#define LEVEL_BUFFER_SIZE 20

typedef struct UpgradeMenuItems
{
	Upgrade upgrade;
	char costText[COST_BUFFER_SIZE];
	char levelText[LEVEL_BUFFER_SIZE];
	Button btnBuy;
	CP_Vector pos;

}UpgradeMenuItem;

void Asteroids_Upgrades_Menu_Init(void);
void Asteroids_Upgrades_Menu_Update(void);
void Asteroids_Upgrades_Menu_Draw(void);
UpgradeMenuItem Asteroids_Upgrades_Menu_Update_Upgrade_Info_Text(UpgradeMenuItem menuItem);
UpgradeMenuItem Asteroids_Upgrades_Menu_Init_Upgrade_Info(Upgrade upgrade, CP_Vector pos, void(*callback)(void* ptr));
void Asteroids_Upgrades_Menu_Display_Upgrade_Info(UpgradeMenuItem* menuItem);
void Asteroids_Upgrades_Menu_Update_Upgrade_Info(UpgradeMenuItem* menuItem);
void Asteroids_Upgrades_Menu_Upgrade_Add_Level(void* upgradePtr);
void Asteroids_Upgrades_Menu_Reset_Upgrades();
void Asteroids_Upgrades_Menu_Refresh_Items();
void Asteroids_Upgrades_Menu_Display_Balance(CP_Color Color, CP_Vector pos);
void Asteroids_Upgrades_Menu_Init_MenuItems();
void Asteroids_Upgrades_Menu_Create_MenuItem(unsigned int id, CP_Vector pos, void(*callback)(void* ptr));
void Asteroids_Upgrades_Menu_Add_MenuItem(UpgradeMenuItem item);
void Asteroids_Upgrades_Menu_Display_Items();