#include "user_interface.h"
#include "cprocessing.h"
#include <stdio.h>
#include "utility.h"

static CP_Image heart_sprite;
static CP_Vector fuelPos;

void Asteroids_UI_Init()
{
	fuelPos = CP_Vector_Set((float)WIN_WIDTH - 100, (float)WIN_HEIGHT / 2);
}

void Asteroids_UI_Update(Player player)
{
	Asteroids_UI_Draw(player);
}

void Asteroids_UI_Draw(Player player)
{
	Asteroids_UI_Health_HP_Draw(player.hp);
	Asteroids_UI_Fuel_Draw(player.engine.fuel);
}

void Asteroids_UI_Health_HP_Draw(Health hp)
{
	float width = ASTEROIDS_UI_PLAYER_HEALTH_BAR_WIDTH;
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	CP_Settings_TextSize(50);
	CP_Font_DrawText("HP:", 60, 70);

	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(100, 50, hp.max/hp.max * width, 50);

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(100, 50, hp.current/hp.max * width, 50);
}

void Asteroids_UI_Fuel_Draw(Fuel fuel)
{
	float width = ASTEROIDS_UI_PLAYER_FUEL_METER_BAR_WIDTH;
	float height = ASTEROIDS_UI_PLAYER_FUEL_METER_BAR_HEIGHT;
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	CP_Vector pos = fuelPos;
	pos.y -= height / 2;

	float backgroundHeight = fuel.max / fuel.max * height;
	float foregroundHeight = fuel.current / fuel.max * height;

	CP_Settings_TextSize(40);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("Fuel", pos.x + 20, pos.y - 35);

	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255)); //Orange
	CP_Graphics_DrawRect(pos.x, pos.y, width, backgroundHeight);

	CP_Settings_Fill(CP_Color_Create(235, 146, 52, 255)); //Orange
	CP_Graphics_DrawRect(pos.x, pos.y + (backgroundHeight - foregroundHeight), width, foregroundHeight);
}