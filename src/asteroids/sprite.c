//---------------------------------------------------------
// file:	sprite.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Simple Sprite system for animation
//			Contains functions for creating sprites (animated).
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "sprite.h"

Sprite Asteroids_Sprite_Create_Animated(CP_Image images[], CP_Vector dimensions[], int frame_count, float duration, int start_frame)
{
	Sprite sprite;
	sprite.animated = 1;
	sprite.images = images;
	sprite.dimensions = dimensions;
	sprite.frame_count = frame_count;
	sprite.duration = duration; //entire particle effect lifetime
	sprite.keyframe = start_frame;
	sprite.time = duration / frame_count; //lifetime of one frame
	return sprite;
}

Sprite Asteroids_Sprite_Create_Static(CP_Image image, CP_Vector dimensions)
{
	Sprite sprite;
	sprite.image = image;
	sprite.width = dimensions.x;
	sprite.height = dimensions.y;
	return sprite;
}