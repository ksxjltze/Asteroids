#include "tutorial.h"
#include "player.h"
#include "constants.h"
#include "game.h"
#include "audio_manager.h"
#include "utility.h"
#include "state.h"

Player player;
CP_Image player_sprite;
static float text_row_width;
State tutorialState;

enum tutorialStateType { TUTORIAL_MOVE };

void Asteroids_Tutorial_Init()
{
	player_sprite = CP_Image_Load(ASTEROIDS_PLAYER_SPRITE_PATH_DEFAULT);
	player = Asteroids_Player_Init(ASTEROIDS_PLAYER_SPRITE_WIDTH, ASTEROIDS_PLAYER_SPRITE_HEIGHT, false);
	text_row_width = 100;

	tutorialState.id = TUTORIAL_MOVE;
	tutorialState.name = "MOVE";
	tutorialState.action = &Asteroids_Tutorial_State_Move_Tutorial;
	Asteroids_Audio_Manager_Init();
}

void Asteroids_Tutorial_Update()
{
	Asteroids_Player_Update(&player);
	Asteroids_Player_Draw(player_sprite, player.pos, ASTEROIDS_PLAYER_SPRITE_WIDTH, ASTEROIDS_PLAYER_SPRITE_HEIGHT, 255, player.rotation);
	Asteroids_Tutorial_State_Update();
}

void Asteroids_Tutorial_State_Update()
{
	tutorialState.action(&player);
}

void Asteroids_Tutorial_State_Move_Tutorial(void* context)
{
	if (context)
	{
		Asteroids_Tutorial_DrawText(Asteroids_Utility_GetWindowMiddle(), "TEST");
	}
}

void Asteroids_Tutorial_DrawText(CP_Vector pos, const char* text)
{
	CP_Font_DrawTextBox(text, pos.x, pos.y, text_row_width);
}

void Asteroids_Tutorial_Exit()
{
	Asteroids_Audio_Manager_Exit();
}