#include "utility.h"

/*
@brief Generates a random position on the screen (window).
*/
CP_Vector Asteroids_Utility_Generate_Random_Pos()
{
	float x = (float)(CP_Random_GetInt() % CP_System_GetWindowWidth());
	float y = (float)(CP_Random_GetInt() % CP_System_GetWindowHeight());

	return CP_Vector_Set(x, y);
}

//@brief Generates a red tinted sprite to serve as a "hurt sprite".
void Asteroids_Utility_Generate_Hurt_Sprite(CP_Image sprite, CP_Image* out)
{
	unsigned char* pixels = malloc(CP_Image_GetPixelBufferSize(sprite));
	CP_Image_GetPixelData(sprite, pixels);

	//Create Enemy Hurt Sprite from modified enemy_sprite pixel data.
	if (pixels)
	{
		for (int i = 0; i < CP_Image_GetPixelBufferSize(sprite); i++)
		{
			if (i % 4 == 3) //alpha
			{
				continue;
			}

			if (i % 4 == 0) //red
			{
				if (i < 1)
					continue;

				if (pixels[i - 1] > 0)
					pixels[i - 1] = 255;
			}
			else
				pixels[i] = 0;

		}

	}

	CP_Image image = CP_Image_CreateFromData(CP_Image_GetWidth(sprite), CP_Image_GetHeight(sprite), pixels);
	*out = image;
	
	free(pixels);
	
	return;
}

/// <summary>
/// Get the CP_Vector position of the center of the window.
/// </summary>
/// <returns>CP_Vector position</returns>
CP_Vector Asteroids_Utility_GetWindowMiddle()
{
	return CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
}

//Helper function for determining if mouse is over object (Rect).
//Object position must start at top left corner.
bool isMouseOver_Rect(CP_Vector position, float width, float height, float mouseX, float mouseY)
{
	bool left = position.x <= mouseX;
	bool right = position.x + width >= mouseX;
	bool top = position.y <= mouseY;
	bool bottom = position.y + height >= mouseY;

	return left && right && top && bottom;
}

bool Asteroids_Utility_isInWindow(CP_Vector position)
{
	bool left = position.x > 0;
	bool right = position.x < WIN_WIDTH;
	bool top = position.y > 0;
	bool bottom = position.y < WIN_HEIGHT;

	return left && right && top && bottom;
}