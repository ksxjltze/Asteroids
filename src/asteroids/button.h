#pragma once
#include "cprocessing.h"

typedef struct Text
{
	float textSize;
	const char* text;
}ButtonText;

typedef struct Buttons
{
	void(*function)();
	ButtonText textbox;

	CP_Vector position;
	float width, height;
}Button;

Button Asteroids_Button_Add_New_Button();
void Asteroids_Button_Init(Button* button_out);
void Asteroids_Button_Update(Button* button);
void Asteroids_Button_Draw(Button button);
void Asteroids_Button_Draw_Text(ButtonText text);