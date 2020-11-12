#include "user_interface.h"
#include "cprocessing.h"
#include <stdio.h>
#include "utility.h"

static CP_Image heart_sprite;

void Asteroids_UI_Init()
{
	Asteroids_UI_Health_HP_Init();
}

void Asteroids_UI_Update(Health hp)
{
	Asteroids_UI_Draw(hp);
}

void Asteroids_UI_Draw(Health hp)
{
	Asteroids_UI_Health_HP_Draw(hp);
}

void Asteroids_UI_Health_HP_Draw(Health hp)
{
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(100, 50, hp.max/hp.max * ASTEROIDS_UI_PLAYER_HEALTH_BAR_WIDTH, 50);
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(100, 50, hp.current/hp.max * 300, 50);
}

void Asteroids_UI_Health_HP_Init()
{

}