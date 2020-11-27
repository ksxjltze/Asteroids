#include "upgrades_menu.h"
#include <stdio.h>
#include "utility.h"
#include "constants.h"
#include "currency.h"
#include "file_manager.h"

UpgradeMenuItem menuItems[NUM_UPGRADES];

void Asteroids_Upgrades_Menu_Init(void)
{
	Asteroids_Upgrades_Menu_Init_MenuItems();

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
}

void Asteroids_Upgrades_Menu_Update(void)
{
	Asteroids_Upgrades_Menu_Draw();
	Asteroids_Upgrades_Menu_Display_Items();
}

void Asteroids_Upgrades_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	Asteroids_Upgrades_Menu_Display_Balance();
}

void Asteroids_Upgrades_Menu_Display_Balance(void)
{
	CP_Settings_TextSize(30);
	int balance = Asteroids_Currency_Get_Balance();
	char balanceText[BALANCE_BUFFER_SIZE];
	sprintf_s(balanceText, BALANCE_BUFFER_SIZE, "Balance: %d\n", balance);
	CP_Font_DrawText(balanceText, 100, 30);
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

void Asteroids_Upgrades_Menu_Display_Items()
{
	for (int i = 0; i < NUM_UPGRADES; i++)
	{
		if (menuItems[i].upgrade.id != NONE)
		{
			Asteroids_Upgrades_Menu_Display_Upgrade_Info(menuItems + i);
		}
	}
}

UpgradeMenuItem Asteroids_Upgrades_Menu_Init_Upgrade_Info(Upgrade upgrade, CP_Vector pos, void(*callback)(void* ptr))
{
	UpgradeMenuItem menuItem;
	menuItem.upgrade = upgrade;
	menuItem.pos = pos;

	char costText[COST_BUFFER_SIZE];
	sprintf_s(costText, COST_BUFFER_SIZE, "Cost: %d\n", upgrade.cost);
	strcpy_s(menuItem.costText, strlen(costText) + 1, costText);

	char levelText[LEVEL_BUFFER_SIZE];
	sprintf_s(levelText, LEVEL_BUFFER_SIZE, "Level: %d\n", upgrade.level);
	strcpy_s(menuItem.levelText, strlen(levelText) + 1, levelText);

	menuItem.btnBuy = Asteroids_Button_Add_New_Button(120, 30);
	CP_Vector btnPos = pos;
	btnPos.x -= menuItem.btnBuy.width / 2;

	Asteroids_Button_Set_Position(&menuItem.btnBuy, btnPos);
	Asteroids_Button_Set_Text(&menuItem.btnBuy, 20, "BUY");
	Asteroids_Button_Set_Callback_Pointer(callback, &menuItem.btnBuy);

	return menuItem;
}

void Asteroids_Upgrades_Menu_Display_Upgrade_Info(UpgradeMenuItem* menuItem)
{
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText(menuItem->upgrade.name, menuItem->pos.x, menuItem->pos.y - 80);

	Asteroids_Button_Update_Advanced(&menuItem->btnBuy, menuItem);

	CP_Settings_TextSize(30);
	CP_Font_DrawText(menuItem->costText, menuItem->pos.x, menuItem->pos.y - 50);
	CP_Font_DrawText(menuItem->levelText, menuItem->pos.x, menuItem->pos.y - 20);

}

void Asteroids_Upgrades_Menu_Update_Upgrade_Info(UpgradeMenuItem* menuItem)
{
	menuItem->upgrade = Asteroids_Upgrades_Get_Upgrade(menuItem->upgrade.id);
	char levelText[LEVEL_BUFFER_SIZE];
	sprintf_s(levelText, LEVEL_BUFFER_SIZE, "Level: %d\n", menuItem->upgrade.level);
	strcpy_s(menuItem->levelText, strlen(levelText) + 1, levelText);
}

void Asteroids_Upgrades_Menu_Upgrade_Add_Level(void* upgradePtr)
{
	UpgradeMenuItem* menuItem = (UpgradeMenuItem*)upgradePtr;
	if (Asteroids_Currency_Deduct_Balance(menuItem->upgrade.cost))
	{
		Asteroids_Upgrade_Add_Level(menuItem->upgrade.id);
		Asteroids_Upgrades_Menu_Update_Upgrade_Info(menuItem);
		Asteroids_Upgrades_Save_All_To_File();
	}
}