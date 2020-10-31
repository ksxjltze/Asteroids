#include "gameover.h"

void gameover_init(void)
{
	settings_setup(WIN_WIDTH, WIN_HEIGHT);
}

void gameover_update(void)
{

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(200.0f);
	CP_Font_DrawText("GAME OVER", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	if (CP_Input_MouseClicked())
	{
		CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
		CP_Engine_Run();
	}
}

void gameover_exit(void)
{

}