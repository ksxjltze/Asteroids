#include "utility.h"

/*
@brief Generates a random position on the screen (window).
*/
CP_Vector generate_random_pos()
{
	float x = (float)(CP_Random_GetInt() % WIN_WIDTH);
	float y = (float)(CP_Random_GetInt() % WIN_HEIGHT);

	return CP_Vector_Set(x, y);
}

//@brief Generates a red tinted sprite to serve as a "hurt sprite".
void generate_hurt_sprite(CP_Image sprite, CP_Image* out)
{
	unsigned char* pixels = malloc(CP_Image_GetPixelBufferSize(sprite));
	CP_Image_GetPixelData(sprite, pixels);

	//Create Enemy Hurt Sprite from modified enemy_sprite pixel data.
	if (pixels)
	{
		for (int i = 0; i < CP_Image_GetPixelBufferSize(sprite); ++i)
		{
			if (i % 4 == 3) //alpha
			{
				continue;
			}

			if (i % 4 == 0) //red
			{
				if (pixels[i - 1] > 0)
					pixels[i - 1] = 255;
			}
			else
				pixels[i] = 0;

		}

	}

	CP_Image image = CP_Image_CreateFromData(CP_Image_GetWidth(sprite), CP_Image_GetHeight(sprite), pixels);
	*out = image;
	return;
}