#include "user_interface.h"
#include "cprocessing.h"
#include <stdio.h>
#include "utility.h"
#include "constants.h"
#include "game.h"
#include "final_boss.h"

static CP_Image heart_sprite;
static CP_Vector fuelPos;
static CP_Vector difficultyPos;
static float timePassed;
static CP_Color meterFill;
static CP_Color nextFill;

void Asteroids_UI_Init()
{
	fuelPos = CP_Vector_Set((float)WIN_WIDTH - 100, (float)WIN_HEIGHT / 2);
	difficultyPos = CP_Vector_Set((float)WIN_WIDTH - 120, 40);
	timePassed = 0;
	meterFill = CP_Color_Create(0, 255, 0, 255);
	nextFill = meterFill;
}

void Asteroids_UI_Update(Player player)
{
	if (ASTEROIDS_GAME_DIFFICULTY < BRUH)
	{
		if (!endgame.end)
			timePassed += CP_System_GetDt();
	}
	else if (timePassed != ASTEROIDS_DIFFICULTY_INTERVAL)
	{
		timePassed = ASTEROIDS_DIFFICULTY_INTERVAL;
		meterFill.r = 255;
		meterFill.g = 0;
		meterFill.b = 255;
	}
	
	Asteroids_UI_Draw(player);
}

void Asteroids_UI_Draw(Player player)
{
	Asteroids_UI_Health_HP_Draw(player.hp);
	Asteroids_UI_Fuel_Draw(player.engine.fuel);
	Asteroids_UI_Display_Current_Difficulty();
}

void Asteroids_UI_Health_HP_Draw(Health hp)
{
	float width = ASTEROIDS_UI_PLAYER_HEALTH_BAR_WIDTH;
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	CP_Settings_TextSize(50);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
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

void Asteroids_UI_Display_Current_Difficulty(void)
{
	CP_Settings_TextSize(30);
	Asteroids_UI_Display_Difficulty_Meter();
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (ASTEROIDS_GAME_DIFFICULTY >= BRUH)
	{
		CP_Font_DrawText("BRUH", difficultyPos.x, difficultyPos.y);
	}


	switch (ASTEROIDS_GAME_DIFFICULTY)
	{
	case EASY:
		CP_Font_DrawText("EASY", difficultyPos.x, difficultyPos.y);
		break;
	case NORMAL:
		CP_Font_DrawText("NORMAL", difficultyPos.x, difficultyPos.y);
		break;
	case HARD:
		CP_Font_DrawText("HARD", difficultyPos.x, difficultyPos.y);
		break;
	case INSANE:
		CP_Font_DrawText("INSANE", difficultyPos.x, difficultyPos.y);
		break;
	case IMPOSSIBLE:
		CP_Font_DrawText("IMPOSSIBLE", difficultyPos.x, difficultyPos.y);
		break;
	case PEPEGA:
		CP_Font_DrawText("PEPEGA", difficultyPos.x, difficultyPos.y);
		break;
	}
}

void Asteroids_UI_Display_Difficulty_Meter()
{
	meterFill = CP_Color_Lerp(meterFill, nextFill, CP_System_GetDt());
	if (timePassed >= ASTEROIDS_DIFFICULTY_INTERVAL && ASTEROIDS_GAME_DIFFICULTY < BRUH)
	{
		timePassed = 0;

		if (nextFill.r < 255)
		{
			int scale = 40;
			nextFill.r += scale * 3;
			nextFill.g -= scale * 2;
			nextFill.b += scale;
		}
	}

	CP_Vector meterPos = CP_Vector_Set(difficultyPos.x - 100, difficultyPos.y - 20);
	float meterWidth = 200, meterHeight = 40;

	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(meterPos.x, meterPos.y, meterWidth, meterHeight);

	CP_Settings_Fill(meterFill);
	CP_Graphics_DrawRect(meterPos.x, meterPos.y, (timePassed / ASTEROIDS_DIFFICULTY_INTERVAL) * meterWidth, meterHeight);

}