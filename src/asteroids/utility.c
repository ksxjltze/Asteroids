//---------------------------------------------------------
// file:	utility.c
// author:	Lee Jia Keat
//
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Utility file which contains helper functions used often in the code base.
//			
// 
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "utility.h"
#include <stdio.h>

/*
@brief Generates a random position on the screen (window).
*/
CP_Vector Asteroids_Utility_Generate_Random_Pos()
{
	float x = (float)(CP_Random_GetInt() % CP_System_GetWindowWidth());
	float y = (float)(CP_Random_GetInt() % CP_System_GetWindowHeight());

	return CP_Vector_Set(x, y);
}

CP_Vector Asteroids_Utility_Generate_Random_Pos_Var2(float width, float height)
{
	float x = CP_Random_RangeFloat(width / 2, CP_System_GetWindowWidth() - width / 2);
	float y = CP_Random_RangeFloat(height / 2, CP_System_GetWindowHeight() - height / 2);

	return CP_Vector_Set(x, y);
}

CP_Vector Asteroids_Utility_Find_Closest_Enemy(Enemy enemy_pool[], CP_Vector pos, CP_Vector* direction_out)
{
	CP_Vector Nearest = CP_Vector_Zero();
	CP_Vector target = CP_Vector_Zero();
	float distance = (float)WIN_WIDTH;

	for (int i = 0; i < ASTEROIDS_POOLSIZE_ENEMIES; i++)
	{
		if (!enemy_pool[i].active)
			continue;
		
		if (!Asteroids_Utility_isInWindow(enemy_pool[i].pos))
			continue;

		float displacement = CP_Vector_Distance(enemy_pool[i].pos, pos);

		if (fabsf(displacement) < distance)
		{
			target = enemy_pool[i].pos;
			distance = displacement;
			Nearest = CP_Vector_Subtract(enemy_pool[i].pos, pos);
		}
	}
	*direction_out = CP_Vector_Normalize(Nearest);
	return target;
	
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

void Asteroids_Utility_Generate_Blue_Sprite(CP_Image sprite, CP_Image* out)
{
	unsigned char* pixels = malloc(CP_Image_GetPixelBufferSize(sprite));
	CP_Image_GetPixelData(sprite, pixels);
	//Create Enemy Hurt Sprite from modified enemy_sprite pixel data.
	if (pixels)
	{
		for (int i = 0; i < CP_Image_GetPixelBufferSize(sprite); i++)
		{
			if (i % 4 != 2) //not blue
			{
				if (i % 4 == 1)
				{
					pixels[i] = 100;
					continue;
				}
				if (i > 2)
				{
					if (i % 4 != 3)
						pixels[i] = 0;

				}
			}
			else
			{
				pixels[i] = 255;
			}
				
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

void Asteroids_Utility_Move_Object_To_Mouse(CP_Vector* position)
{
	*position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

void Asteroids_Utility_Move_Object_To_Mouse_Stationary(CP_Vector* position, CP_Vector* velocity)
{
	*position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	*velocity = CP_Vector_Zero();
}

float Asteroids_Utility_Get_Rotation_Angle_To_Mouse(CP_Vector position)
{
	CP_Vector mousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	CP_Vector direction = CP_Vector_Subtract(mousePos, position);

	CP_Vector vec_up = CP_Vector_Set(0, -1);
	CP_Vector vec_right = CP_Vector_Set(1, 0);

	float dot = CP_Vector_DotProduct(direction, vec_right);

	float rotation = 0;

	if (dot >= 0)
		rotation = CP_Vector_Angle(direction, vec_up);
	else if (dot < 0)
		rotation = -CP_Vector_Angle(direction, vec_up);

	return rotation;
}
