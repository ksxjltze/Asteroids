#include "button.h"

Button Asteroids_Button_Add_New_Button()
{
	Button button;
	Asteroids_Button_Init(&button);

	return button;
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