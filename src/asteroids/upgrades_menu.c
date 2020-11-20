#include "upgrades_menu.h"
#include <stdio.h>
#include "utility.h"
#include "constants.h"
#include "currency.h"

#define BALANCE_BUFFER_SIZE 100
#define COST_BUFFER_SIZE 20
#define LEVEL_BUFFER_SIZE 10

UpgradeMenuItem menuItem_FuelCapacity;

void Asteroids_Upgrades_Menu_Init(void)
{
	menuItem_FuelCapacity = Asteroids_Upgrades_Menu_Init_Upgrade_Info(Asteroids_Upgrades_Get_Upgrade(FUEL_CAPACITY), Asteroids_Utility_GetWindowMiddle(), &Asteroids_Upgrades_Menu_Upgrade_Add_Level);
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
	Asteroids_Upgrades_Menu_Display_Upgrade_Info(menuItem_FuelCapacity);
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

	static char costText[COST_BUFFER_SIZE];
	sprintf_s(costText, COST_BUFFER_SIZE, "Cost: %d\n", upgrade.cost);
	menuItem.costText = costText;

	static char levelText[LEVEL_BUFFER_SIZE];
	sprintf_s(levelText, LEVEL_BUFFER_SIZE, "Level: %d\n", upgrade.level);
	menuItem.levelText = levelText;

	menuItem.btnBuy = Asteroids_Button_Add_New_Button(120, 30);
	CP_Vector btnPos = pos;
	btnPos.x -= menuItem.btnBuy.width / 2;

	Asteroids_Button_Set_Position(&menuItem.btnBuy, btnPos);
	Asteroids_Button_Set_Text(&menuItem.btnBuy, 20, "BUY");
	Asteroids_Button_Set_Callback_Pointer(callback, &menuItem.btnBuy);

	return menuItem;
}

void Asteroids_Upgrades_Menu_Display_Upgrade_Info(UpgradeMenuItem menuItem)
{
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText(menuItem.upgrade.name, menuItem.pos.x, menuItem.pos.y - 150);

	Asteroids_Button_Update_Advanced(&menuItem.btnBuy, &menuItem);
	CP_Font_DrawText(menuItem.costText, menuItem.pos.x, menuItem.pos.y - 100);
	CP_Font_DrawText(menuItem.levelText, menuItem.pos.x, menuItem.pos.y - 50);

}

void Asteroids_Upgrades_Menu_Update_Upgrade_Info(UpgradeMenuItem* menuItem, unsigned int level)
{
	static char levelText[LEVEL_BUFFER_SIZE];
	sprintf_s(levelText, LEVEL_BUFFER_SIZE, "Level: %d\n", menuItem->upgrade.level);
	menuItem->levelText = levelText;
}

void Asteroids_Upgrades_Menu_Upgrade_Add_Level(void* upgradePtr)
{
	UpgradeMenuItem* menuItem = (UpgradeMenuItem*)upgradePtr;
	if (Asteroids_Currency_Deduct_Balance(ASTEROIDS_UPGRADES_FUEL_UPGRADE_COST))
	{
		Asteroids_Upgrade_Add_Level(menuItem->upgrade.id);
		Asteroids_Upgrades_Menu_Update_Upgrade_Info(menuItem, menuItem->upgrade.level);
	}
}