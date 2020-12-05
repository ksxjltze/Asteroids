#pragma once
#include "cprocessing.h"

typedef struct Sprites
{
	CP_Image* images;
	CP_Vector* dimensions;
	int animated;
	CP_Image image;
	float width;
	float height;
	int keyframe;
	int frame_count;
	float duration;
	float time;
}Sprite;

Sprite Asteroids_Sprite_Create_Animated(CP_Image images[], CP_Vector dimensions[], int frame_count, float duration, int start_frame);
Sprite Asteroids_Sprite_Create_Static(CP_Image image, CP_Vector dimensions);
