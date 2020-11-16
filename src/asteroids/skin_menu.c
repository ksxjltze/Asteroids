#include "skin_menu.h"
#include "cprocessing.h"
#include "utility.h"

typedef struct Skins
{
	CP_Image sprite;
	const char* name;
	float cost;
}Skin;

static Skin current_skin;
static CP_Vector skinDisplayPos;
static float displayScaleFactor;

void Asteroids_Skin_Menu_Init(void)
{
	current_skin.sprite = NULL;
	current_skin.name = "NULL";
	current_skin.cost = 0;
	skinDisplayPos = Asteroids_Utility_GetWindowMiddle();
	displayScaleFactor = 3.0f;

}

void Asteroids_Skin_Menu_Update(void)
{
	CP_Image_Draw(current_skin.sprite, skinDisplayPos.x, skinDisplayPos.y, ASTEROIDS_PLAYER_SPRITE_WIDTH * displayScaleFactor, ASTEROIDS_PLAYER_SPRITE_HEIGHT * displayScaleFactor, 255);
}

void Asteroids_Skin_Menu_Draw(void)
{

}