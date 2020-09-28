#include "menu.h"
#include "game.h"
#include "cprocessing.h"
#include "constants.h"
#include "init.h"
#include "splash.h"

CP_Image splash;

void menu_init(void)
{
	init_menu_settings(WIN_WIDTH, WIN_HEIGHT);
	splash = CP_Image_Load("./Assets/DigiPen_WHITE.png");

}

void menu_update(void)
{
	if (display_splash(SPLASH_DURATION, splash))
		return;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("CLICK ANYWHERE TO START", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	if (CP_Input_MouseClicked())
	{
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		CP_Engine_Run();
	}

}

void menu_exit(void)
{

}