#include "upgrades_menu.h"
#include "button.h"
#include "utility.h"
#include "constants.h"
#include <stdio.h>

Button testBtn;

void Asteroids_Upgrades_Menu_Init(void)
{
	CP_Vector pos;
	pos = Asteroids_Utility_GetWindowMiddle();
	testBtn = Asteroids_Button_Add_New_Button(300, 100);
	pos.x -= testBtn.width / 2;
	pos.y = WIN_HEIGHT * 0.2f;

	Asteroids_Button_Set_Position(&testBtn, pos);
	Asteroids_Button_Set_Text(&testBtn, 40, "TEST");
	Asteroids_Button_Set_Callback_Void(&Asteroids_Upgrades_Menu_Test, &testBtn);

}

void Asteroids_Upgrades_Menu_Update(void)
{
	Asteroids_Upgrades_Menu_Draw();
	Asteroids_Button_Update(&testBtn);
}

void Asteroids_Upgrades_Menu_Draw(void)
{
	CP_Vector pos = Asteroids_Utility_GetWindowMiddle();
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("TEST", pos.x, pos.y);
}

void Asteroids_Upgrades_Menu_Test(void)
{
	printf("TEST");
}