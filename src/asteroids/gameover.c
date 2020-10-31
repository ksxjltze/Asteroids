#include "gameover.h"

void Asteroids_GameOver_Init(void)
{
	Asteroids_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);
}

void Asteroids_GameOver_Update(void)
{

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(200.0f);
	CP_Font_DrawText("GAME OVER", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	if (CP_Input_MouseClicked())
	{
		CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
		CP_Engine_Run();
	}
}

void Asteroids_GameOver_Exit(void)
{

}