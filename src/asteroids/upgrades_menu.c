#include "upgrades_menu.h"
#include <stdio.h>
#include "utility.h"
#include "constants.h"
#include "currency.h"
#include "file_manager.h"

UpgradeMenuItem menuItem_FuelCapacity;
UpgradeMenuItem menuItem_MaxHealth;

void Asteroids_Upgrades_Menu_Init(void)
{
	CP_Vector pos1 = CP_Vector_Set(WIN_WIDTH * 0.1f, WIN_HEIGHT * 0.25f);
	CP_Vector pos2 = CP_Vector_Set(WIN_WIDTH * 0.25f, WIN_HEIGHT * 0.25f);

	menuItem_FuelCapacity = Asteroids_Upgrades_Menu_Init_Upgrade_Info(Asteroids_Upgrades_Get_Upgrade(FUEL_CAPACITY), pos1, &Asteroids_Upgrades_Menu_Upgrade_Add_Level);
	menuItem_MaxHealth = Asteroids_Upgrades_Menu_Init_Upgrade_Info(Asteroids_Upgrades_Get_Upgrade(MAX_HEALTH), pos2, &Asteroids_Upgrades_Menu_Upgrade_Add_Level);
}

void Asteroids_Upgrades_Menu_Display_Balance(void)
{
	CP_Settings_TextSize(30);
	int balance = Asteroids_Currency_Get_Balance();
	char balanceText[BALANCE_BUFFER_SIZE];
	sprintf_s(balanceText, BALANCE_BUFFER_SIZE, "Balance: %d\n", balance);
	CP_Font_DrawText(balanceText, 100, 30);
}

void Asteroids_Upgrades_Menu_Update(void)
{
	Asteroids_Upgrades_Menu_Draw();
	Asteroids_Upgrades_Menu_Display_Upgrade_Info(&menuItem_FuelCapacity);
	Asteroids_Upgrades_Menu_Display_Upgrade_Info(&menuItem_MaxHealth);
}

void Asteroids_Upgrades_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	Asteroids_Upgrades_Menu_Display_Balance();
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
	if (Asteroids_Currency_Deduct_Balance(ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST))
	{
		Asteroids_Upgrade_Add_Level(menuItem->upgrade.id);
		Asteroids_Upgrades_Menu_Update_Upgrade_Info(menuItem);
		Asteroids_Upgrades_Save_All_To_File();
	}
}