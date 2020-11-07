#include "health.h"
#include "cprocessing.h"
#include <stdio.h>
#include "utility.h"

static CP_Image heart_sprite;

void Asteroids_Health_UI_Draw(Health hp)
{
	if (heart_sprite)
		CP_Image_Draw(heart_sprite, 100, 100, 100, 100, 255);
		
}

void Asteroids_Health_UI_Init()
{
	heart_sprite = NULL;
	heart_sprite = CP_Image_Load(ASTEROIDS_HEART_SPRITE_PATH);
	if (!heart_sprite)
		fprintf(stderr, "%s:%s\n", ASTEROIDS_ERROR_STR_MISSING_SPRITE, getVarName(heart_sprite));
}