#include "difficulty_menu.h"
#include "button.h"
#include "utility.h"

static Button difficultyButton;

void Asteroids_Difficulty_Menu_Init(void)
{
	CP_Vector pos = Asteroids_Utility_GetWindowMiddle();
	difficultyButton = Asteroids_Button_Add_New_Button(300, 100);
	pos.x -= difficultyButton.width / 2;
	pos.y -= difficultyButton.height / 2;

	Asteroids_Button_Set_Position(&difficultyButton, pos);
	Asteroids_Difficulty_Menu_Update_ButtonText(&difficultyButton);
	Asteroids_Button_Set_Callback_Button(&Asteroids_Difficulty_Set_NextDifficulty, &difficultyButton);

}

void Asteroids_Difficulty_Menu_Update_ButtonText(Button* button)
{
	float textSize = button->textbox.textSize;
	if (textSize == 0)
	{
		button->textbox.textSize = 50.0f;
		textSize = button->textbox.textSize;
	}

	switch (DIFFICULTY_OPTION)
	{
	case EASY:
		Asteroids_Button_Set_Text(button, textSize, "EASY");
		break;
	case NORMAL:
		Asteroids_Button_Set_Text(button, textSize, "NORMAL");
		break;
	case HARD:
		Asteroids_Button_Set_Text(button, textSize, "HARD");
		break;
	case INSANE:
		Asteroids_Button_Set_Text(button, textSize, "INSANE");
	default:
		break;
	}

}

void Asteroids_Difficulty_Menu_Display_Info(void)
{
	switch (DIFFICULTY_OPTION)
	{

	}
}

void Asteroids_Difficulty_Menu_Update(void)
{
	Asteroids_Difficulty_Menu_Draw();
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Current Difficulty:", difficultyButton.position.x + difficultyButton.width / 2, difficultyButton.position.y - 20);
	Asteroids_Button_Update(&difficultyButton);
}

void Asteroids_Difficulty_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
}

void Asteroids_Difficulty_Set_NextDifficulty(Button* button)
{
	DIFFICULTY_OPTION++;
	if (DIFFICULTY_OPTION > INSANE)
		DIFFICULTY_OPTION = EASY;

	Asteroids_Difficulty_Menu_Update_ButtonText(button);

}

