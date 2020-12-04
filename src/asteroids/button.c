//---------------------------------------------------------
// file:	button.c
// author:	Lee Jia Keat
//
// brief:	Button system source file.
//			Handles creation, updating, drawing and executing callbacks for buttons.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "button.h"
#include <stdio.h>
#include "game.h"
#include "audio_manager.h"

Button Asteroids_Button_Add_New_Button(float width, float height)
{
	Button button;
	Asteroids_Button_Init(&button);
	button.width = width;
	button.height = height;

	return button;
}

void Asteroids_Button_Set_Position(Button* button, CP_Vector position)
{
	button->position = position;
}

void Asteroids_Button_Set_Text(Button* button, float textsize, char text[])
{
	textsize = 45.0f;
	button->textbox.text = text;
	button->textbox.textSize = textsize;
}

void Asteroids_Button_Set_Text_Colors(Button* button, CP_Color color)
{
	button->textbox.color = color;
}

void Asteroids_Button_Set_Callback_Void(void(*callback)(), Button* button)
{
	button->callback.void_callback = callback;
}

void Asteroids_Button_Set_Callback_Button(void(*callback)(Button* button), Button* button)
{
	button->callback.button_callback = callback;
}

void Asteroids_Button_Set_Callback_Pointer(void(*callback)(void* ptr), Button* button)
{
	button->callback.pointer_callback = callback;
}

void Asteroids_Button_Set_Colors(Button* button, CP_Color idle, CP_Color hover, CP_Color clicked)
{
	button->colors.idle = idle;
	button->colors.hover = hover;
	button->colors.clicked = clicked;
}

void Asteroids_Button_Init(Button* button_out)
{
	Button button;
	button.callback.void_callback = NULL;
	button.callback.button_callback = NULL;

	button.position = CP_Vector_Zero();
	button.width = 0;
	button.height = 0;

	button.textbox.textSize = 0;
	button.textbox.text = "NULL";
	button.textbox.color = CP_Color_Create(0, 0, 0, 255); //Default white

	button.colors.idle = CP_Color_Create(153, 204, 255, 255);
	button.colors.hover = CP_Color_Create(0, 255, 0, 255);
	button.colors.clicked = CP_Color_Create(255, 0, 0, 255);
	button.colors.disabled = CP_Color_Create(0, 0, 0, 255);
	
	button.status = IDLE;
	button.enabled = true;
	button.hidden = false;

	*button_out = button;
}

void Asteroids_Button_Update(Button* button)
{
	float mouseX, mouseY;
	mouseX = CP_Input_GetMouseX();
	mouseY = CP_Input_GetMouseY();

	if (button->enabled == true)
	{
		if (isMouseOver_Rect(button->position, button->width, button->height, mouseX, mouseY))
		{
			Asteroids_Button_Is_MouseOver_Button(button);
			if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
				Asteroids_Button_Execute_Callback(button);
		}
		else
		{
			button->status = IDLE;
		}
	}
	else
		button->status = DISABLED;

	if (button->hidden == false)
		Asteroids_Button_Draw(*button);

}

void Asteroids_Button_Update_Advanced(Button* button, void* ptr)
{
	float mouseX, mouseY;
	mouseX = CP_Input_GetMouseX();
	mouseY = CP_Input_GetMouseY();

	if (button->enabled == true)
	{
		if (isMouseOver_Rect(button->position, button->width, button->height, mouseX, mouseY))
		{
			Asteroids_Button_Is_MouseOver_Button(button);
			if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
			{
				Asteroids_Button_Execute_Callback(button);
				if (button->callback.pointer_callback)
				{
					button->callback.pointer_callback(ptr);
				}
			}
		}
		else
		{
			button->status = IDLE;
		}
	}
	else
		button->status = DISABLED;

	if (button->hidden == false)
		Asteroids_Button_Draw(*button);
}

void Asteroids_Button_Is_MouseOver_Button(Button* button)
{
	if (button->status != HOVER && button->status != CLICKED)
	{
		button->status = HOVER;
		Asteroids_Audio_Button_Hover_Play();
	}
	else if (CP_Input_MouseDown(MOUSE_BUTTON_1))
		button->status = CLICKED;
}

void Asteroids_Button_Execute_Callback(Button* button)
{
	if (button->callback.void_callback)
		button->callback.void_callback();

	if (button->callback.button_callback)
	{
		button->callback.button_callback(button);
	}
}

void Asteroids_Button_Draw(Button button)
{
	switch (button.status)
	{
	case IDLE:
		CP_Settings_Fill(button.colors.idle);
		break;
	case HOVER:
		CP_Settings_Fill(button.colors.hover);
		break;
	case CLICKED:
		CP_Settings_Fill(button.colors.clicked);
		break;
	case DISABLED:
		CP_Settings_Fill(button.colors.disabled);
		break;
	}

	CP_Graphics_DrawRect(button.position.x, button.position.y, button.width, button.height);
	if (button.textbox.text)
	{
		Asteroids_Button_Draw_Text(button);
	}
}

void Asteroids_Button_Draw_Text(Button button)
{
	CP_Vector textPos = button.position;
	textPos.x += button.width / 2;
	textPos.y += button.height / 2;

	CP_Settings_Fill(button.textbox.color);
	CP_Settings_TextSize(button.textbox.textSize);
	CP_Font_DrawText(button.textbox.text, textPos.x, textPos.y);
}