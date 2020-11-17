#pragma once
#include "cprocessing.h"

typedef struct Sprites
{
	CP_Image* images;
	CP_Vector* dimensions;
	int keyframe;
	int frame_count;
	float duration;
	float time;
}Sprite;

Sprite Asteroids_Sprite_Create(CP_Image images[], CP_Vector dimensions[], int frame_count, float duration, int start_frame);
