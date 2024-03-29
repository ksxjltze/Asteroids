//---------------------------------------------------------
// file:	upgrades_menu.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Upgrades Menu source file.
//			Draws the user interface (menu) for
//			purchasing upgrades using currency (credits).
//			Displays available upgrades and credits balance/
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "upgrades_menu.h"
#include <stdio.h>
#include "utility.h"
#include "constants.h"
#include "currency.h"
#include "file_manager.h"
#include "button.h"
#include "audio_manager.h"

UpgradeMenuItem menuItems[NUM_UPGRADES];
Button resetBtn;
Button stronkBtn;

void Asteroids_Upgrades_Menu_Init(void)
{
	Asteroids_Upgrades_Menu_Init_MenuItems();
	resetBtn = Asteroids_Button_Add_New_Button(200, 100);
	Asteroids_Button_Set_Text(&resetBtn, 40, "Reset");
	Asteroids_Button_Set_Position(&resetBtn, CP_Vector_Set((float)WIN_WIDTH - resetBtn.width, (float)WIN_HEIGHT - resetBtn.height));
	Asteroids_Button_Set_Callback_Void(&Asteroids_Upgrades_Menu_Reset_Upgrades, &resetBtn);

	stronkBtn = Asteroids_Button_Add_New_Button((float)WIN_WIDTH / 2, 150);
	Asteroids_Button_Set_Text(&stronkBtn, 180, "STRONK");
	Asteroids_Button_Set_Text_Colors(&stronkBtn, CP_Color_Create(255, 0, 255, 255));
	Asteroids_Button_Set_Position(&stronkBtn, CP_Vector_Set((float)WIN_WIDTH / 2 - stronkBtn.width / 2, (float)WIN_HEIGHT * 0.8f - stronkBtn.height));
	Asteroids_Button_Set_Callback_Void(&Asteroids_Upgrades_Menu_STRONK, &stronkBtn);

	int row = 1;
	for (int i = 0; i < Asteroids_Upgrades_Get_Upgrade_Count(); i++)
	{
		CP_Vector pos = CP_Vector_Set(WIN_WIDTH * (0.1f + i * ASTEROIDS_UPGRADES_MENU_ITEM_HORIZONTAL_MARGIN) - WIN_WIDTH * (row - 1), WIN_HEIGHT * ASTEROIDS_UPGRADES_MENU_ITEM_VERTICAL_MARGIN * row);
		if (pos.x > WIN_WIDTH)
		{
			row++;
			pos = CP_Vector_Set(WIN_WIDTH * (0.1f + i * ASTEROIDS_UPGRADES_MENU_ITEM_HORIZONTAL_MARGIN) - WIN_WIDTH * (row - 1), WIN_HEIGHT * ASTEROIDS_UPGRADES_MENU_ITEM_VERTICAL_MARGIN * row);
		}
		Asteroids_Upgrades_Menu_Create_MenuItem(i + 1, pos, &Asteroids_Upgrades_Menu_Upgrade_Add_Level);
	}

	Asteroids_Audio_Manager_BGM_Shop_Play();
}

void Asteroids_Upgrades_Menu_Update(void)
{
	Asteroids_Upgrades_Menu_Draw();
	Asteroids_Upgrades_Menu_Display_Items();
}

void Asteroids_Upgrades_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(160, 160, 160, 255));
	Asteroids_Button_Update(&resetBtn);
	if (DEBUG)
		Asteroids_Button_Update(&stronkBtn);
	Asteroids_Upgrades_Menu_Display_Balance(CP_Color_Create(0, 0, 0, 255), CP_Vector_Set(120, 30));
}

void Asteroids_Upgrades_Menu_Display_Balance(CP_Color Color, CP_Vector pos)
{
	CP_Settings_TextSize(30);
	int balance = Asteroids_Currency_Get_Balance();
	char balanceText[BALANCE_BUFFER_SIZE];
	CP_Settings_Fill(Color);
	sprintf_s(balanceText, BALANCE_BUFFER_SIZE, "Credits: %d\n", balance);
	CP_Font_DrawText(balanceText, pos.x, pos.y);
}

void Asteroids_Upgrades_Menu_Init_MenuItems()
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		Upgrade upgrade = Asteroids_Upgrades_Initialize_Upgrade(NONE, 0, "NONE");
		menuItems[i].upgrade = upgrade;
	}
}

void Asteroids_Upgrades_Menu_Create_MenuItem(unsigned int id, CP_Vector pos, void(*callback)(void* ptr))
{
	UpgradeMenuItem item = Asteroids_Upgrades_Menu_Init_Upgrade_Info(Asteroids_Upgrades_Get_Upgrade(id), pos, callback);
	Asteroids_Upgrades_Menu_Add_MenuItem(item);
}

void Asteroids_Upgrades_Menu_Add_MenuItem(UpgradeMenuItem item)
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (menuItems[i].upgrade.id == NONE)
		{
			menuItems[i] = item;
			break;
		}
	}
}

void Asteroids_Upgrades_Menu_Refresh_Items()
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (menuItems[i].upgrade.id != NONE)
		{
			Asteroids_Upgrades_Menu_Update_Upgrade_Info(&menuItems[i]);
		}
	}
}

void Asteroids_Upgrades_Menu_Display_Items()
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (menuItems[i].upgrade.id != NONE)
		{
			if (menuItems[i].upgrade.prerequisite != NONE)
			{
				if (Asteroids_Upgrade_Check_Prerequisite_Status(menuItems[i].upgrade.prerequisite) == false)
				{
					continue;
				}
			}

			Asteroids_Upgrades_Menu_Display_Upgrade_Info(menuItems + i);
		}
	}
}

void Asteroids_Upgrades_Menu_Reset_Upgrades()
{
	int refund = Asteroids_Upgrades_Reset_Upgrades();
	Asteroids_Currency_Add(refund);
	Asteroids_Upgrades_Menu_Refresh_Items();
}

UpgradeMenuItem Asteroids_Upgrades_Menu_Update_Upgrade_Info_Text(UpgradeMenuItem menuItem)
{
	if (menuItem.upgrade.hasLevel)
	{
		char levelText[LEVEL_BUFFER_SIZE];
		sprintf_s(levelText, LEVEL_BUFFER_SIZE, "Level: %d\n", menuItem.upgrade.level);
		strcpy_s(menuItem.levelText, strlen(levelText) + 1, levelText);
	}
	else
	{
		if (menuItem.upgrade.activated)
			strcpy_s(menuItem.levelText, COST_BUFFER_SIZE, "Purchased.");
		else
			strcpy_s(menuItem.levelText, COST_BUFFER_SIZE, "Not Purchased.");
	}
	return menuItem;
}

UpgradeMenuItem Asteroids_Upgrades_Menu_Init_Upgrade_Info(Upgrade upgrade, CP_Vector pos, void(*callback)(void* ptr))
{
	UpgradeMenuItem menuItem;
	menuItem.upgrade = upgrade;
	menuItem.pos = pos;

	char costText[COST_BUFFER_SIZE];
	sprintf_s(costText, COST_BUFFER_SIZE, "Cost: %d\n", upgrade.cost);
	strcpy_s(menuItem.costText, strlen(costText) + 1, costText);

	menuItem = Asteroids_Upgrades_Menu_Update_Upgrade_Info_Text(menuItem);

	menuItem.btnBuy = Asteroids_Button_Add_New_Button(120, 30);
	CP_Vector btnPos = pos;
	btnPos.x -= menuItem.btnBuy.width / 2;

	Asteroids_Button_Set_Position(&menuItem.btnBuy, btnPos);
	Asteroids_Button_Set_Text(&menuItem.btnBuy, 35, "BUY");
	Asteroids_Button_Set_Callback_Pointer(callback, &menuItem.btnBuy);

	return menuItem;
}

void Asteroids_Upgrades_Menu_Display_Upgrade_Info(UpgradeMenuItem* menuItem)
{
	CP_Settings_TextSize(30.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText(menuItem->upgrade.name, menuItem->pos.x, menuItem->pos.y - 80);

	Asteroids_Button_Update_Advanced(&menuItem->btnBuy, menuItem);

	CP_Settings_TextSize(30);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText(menuItem->costText, menuItem->pos.x, menuItem->pos.y - 50);
	CP_Font_DrawText(menuItem->levelText, menuItem->pos.x, menuItem->pos.y - 20);

}

void Asteroids_Upgrades_Menu_Update_Upgrade_Info(UpgradeMenuItem* menuItem)
{
	menuItem->upgrade = Asteroids_Upgrades_Get_Upgrade(menuItem->upgrade.id);
	*menuItem = Asteroids_Upgrades_Menu_Update_Upgrade_Info_Text(*menuItem);
}

void Asteroids_Upgrades_Menu_Upgrade_Add_Level(void* upgradePtr)
{
	UpgradeMenuItem* menuItem = (UpgradeMenuItem*)upgradePtr;
	if (menuItem->upgrade.prerequisite != NONE)
	{
		if (Asteroids_Upgrade_Check_Prerequisite_Status(menuItem->upgrade.prerequisite) == false)
		{
			printf("Upgrade %s requires prerequisite ID %d.\n", menuItem->upgrade.name, menuItem->upgrade.prerequisite);
			return;
		}
	}

	if (menuItem->upgrade.hasLevel)
	{
		if (menuItem->upgrade.level + 1 > menuItem->upgrade.max_level)
		{
			printf("Upgrade %s is already at the max level.\n", menuItem->upgrade.name);
			return;
		}

		if (Asteroids_Currency_Deduct_Balance(menuItem->upgrade.cost))
		{
			Asteroids_Upgrade_Add_Level(menuItem->upgrade.id);
			Asteroids_Upgrades_Menu_Update_Upgrade_Info(menuItem);
			Asteroids_Upgrades_Save_All_To_File();
		}

	}
	else
	{
		if (!menuItem->upgrade.activated)
		{
			if (Asteroids_Currency_Deduct_Balance(menuItem->upgrade.cost))
			{
				Asteroids_Upgrades_Upgrade_Enable(menuItem->upgrade.id);
				Asteroids_Upgrades_Menu_Update_Upgrade_Info(menuItem);
				Asteroids_Upgrades_Save_All_To_File();
			}
		}
		else
			printf("Upgrade %s is already activated.\n", menuItem->upgrade.name);

	}
}

void Asteroids_Upgrades_Menu_STRONK(void)
{
	Asteroids_Upgrades_STRONK();
	Asteroids_Upgrades_Menu_Refresh_Items();
}
