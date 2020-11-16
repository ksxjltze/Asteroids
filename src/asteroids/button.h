#pragma once
#include "cprocessing.h"
#include <stdbool.h>
#include "utility.h"

typedef int Button_Status;

enum Status_Button
{
	IDLE, HOVER, CLICKED, DISABLED
};

typedef struct Text
{
	float textSize;
	const char* text;
	CP_Color color;
}ButtonText;

typedef struct Colors
{
	CP_Color idle;
	CP_Color hover;
	CP_Color clicked;
	CP_Color disabled;
}ButtonColors;

typedef struct Buttons Button;

typedef struct Callbacks
{
	void(*void_callback)();
	void(*button_callback)(Button* button);
}Callback;

typedef struct Buttons
{
	Callback callback;
	ButtonText textbox;
	ButtonColors colors;

	CP_Vector position;
	float width, height;

	bool enabled;
	bool hidden;
	Button_Status status;
}Button;

Button Asteroids_Button_Add_New_Button(float width, float height);
void Asteroids_Button_Set_Position(Button* button, CP_Vector position);
void Asteroids_Button_Set_Text(Button* button, float textsize, char text[]);
void Asteroids_Button_Set_Text_Colors(Button* button, CP_Color fill);
void Asteroids_Button_Set_Callback_Void(void(*callback)(), Button* button);
void Asteroids_Button_Set_Callback_Button(void(*callback)(Button* button), Button* button);
void Asteroids_Button_Set_Colors(Button* button, CP_Color idle, CP_Color hover, CP_Color clicked);
void Asteroids_Button_Execute_Callback(Button* button);
void Asteroids_Button_Init(Button* button_out);
void Asteroids_Button_Update(Button* button);
void Asteroids_Button_Draw(Button button);
void Asteroids_Button_Draw_Text(Button button);