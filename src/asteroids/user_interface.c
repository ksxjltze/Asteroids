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
	for (float i = 1; i <= hp.current; i++)
	{
		if (heart_sprite)
			CP_Image_Draw(heart_sprite, i * 100, 100, 48, 48, 255);
	}

}

void Asteroids_UI_Health_HP_Init()
{
	heart_sprite = NULL;
	heart_sprite = CP_Image_Load(ASTEROIDS_HEART_SPRITE_PATH);
	if (!heart_sprite)
		fprintf(stderr, "%s:%s\n", ASTEROIDS_ERROR_STR_MISSING_SPRITE, getVarName(heart_sprite));
}