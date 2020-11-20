#include "upgrades_menu.h"
#include "button.h"
#include "utility.h"
#include "constants.h"
#include <stdio.h>
#include "upgrades.h"

Button upgradeBtn_FuelCapacity;

void Asteroids_Upgrades_Menu_Init(void)
{
	CP_Vector pos;
	pos = Asteroids_Utility_GetWindowMiddle();
	upgradeBtn_FuelCapacity = Asteroids_Button_Add_New_Button(300, 100);
	pos.x -= upgradeBtn_FuelCapacity.width / 2;
	pos.y = WIN_HEIGHT * 0.2f;

	Asteroids_Button_Set_Position(&upgradeBtn_FuelCapacity, pos);
	Asteroids_Button_Set_Text(&upgradeBtn_FuelCapacity, 40, "BUY");
	Asteroids_Button_Set_Callback_Void(&Asteroids_Upgrades_Menu_Upgrade_FuelCapacity, &upgradeBtn_FuelCapacity);

}

void Asteroids_Upgrades_Menu_Update(void)
{
	Asteroids_Upgrades_Menu_Draw();
	Asteroids_Button_Update(&upgradeBtn_FuelCapacity);
}

void Asteroids_Upgrades_Menu_Draw(void)
{
	CP_Vector pos = Asteroids_Utility_GetWindowMiddle();
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Fuel Capacity", pos.x, pos.y);
}

void Asteroids_Upgrades_Menu_Upgrade_FuelCapacity(void)
{
	
}