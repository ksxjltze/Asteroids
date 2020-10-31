#include "button.h"

Button Asteroids_Button_Add_New_Button(CP_Vector position, float width, float height)
{
	Button button;
	Asteroids_Button_Init(&button);
	button.position = position;
	button.width = width;
	button.height = height;

	return button;
}

void Asteroids_Button_Set_Text(Button* button, float textsize, char text[])
{
	button->textbox.text = text;
	button->textbox.textSize = textsize;
}

void Asteroids_Button_Set_Callback(void(*callback)())
{

}

void Asteroids_Button_Init(Button* button_out)
{
	Button button;
	button.function = NULL;

	button.position = CP_Vector_Zero();
	button.width = 0;
	button.height = 0;

	button.textbox.textSize = 0;
	button.textbox.text = "";

	*button_out = button;
}

void Asteroids_Button_Update(Button* button)
{

}

void Asteroids_Button_Draw(Button button)
{

}

void Asteroids_Button_Draw_Text(ButtonText text)
{

}