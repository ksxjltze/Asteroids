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
	button.textbox.color = CP_Color_Create(255, 255, 255, 255); //Default white

	button.colors.idle = CP_Color_Create(0, 0, 255, 255);
	button.colors.hover = CP_Color_Create(0, 255, 255, 255);
	button.colors.clicked = CP_Color_Create(255, 255, 255, 255);
	button.colors.disabled = CP_Color_Create(0, 0, 255, 255);

	button.enabled = false;
	*button_out = button;
}

void Asteroids_Button_Update(Button* button)
{
	Asteroids_Button_Draw(*button);
}

void Asteroids_Button_Draw(Button button)
{
	CP_Settings_Fill(button.colors.idle);
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
	CP_Font_DrawText(button.textbox.text, textPos.x, textPos.y);
}