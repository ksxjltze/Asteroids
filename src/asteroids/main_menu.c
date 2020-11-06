#include "main_menu.h"
#include "game.h"
#include "cprocessing.h"
#include "constants.h"
#include "init.h"

void Asteroids_MainMenu_Init(void)
{
	Asteroids_Menu_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);

}

void Asteroids_MainMenu_Update(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("CLICK ANYWHERE TO START", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	if (CP_Input_MouseClicked())
	{
		CP_Engine_SetNextGameState(Asteroids_Init, Asteroids_Update, Asteroids_Exit);
		CP_Engine_Run();
	}

}

void Asteroids_MainMenu_Exit(void)
{

}