#include "sprite.h"

Sprite Asteroids_Sprite_Create(CP_Image images[], CP_Vector dimensions[], int frame_count, float duration, int start_frame)
{
	Sprite sprite;
	sprite.images = images;
	sprite.dimensions = dimensions;
	sprite.frame_count = frame_count;
	sprite.duration = duration;
	sprite.keyframe = start_frame;
	sprite.time = 0;
	return sprite;
}