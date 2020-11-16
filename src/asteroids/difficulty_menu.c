#include "difficulty_menu.h"
#include "button.h"
#include "game.h"
#include "utility.h"

static Button difficultyButton;

void Asteroids_Difficulty_Menu_Init(void)
{
	CP_Vector pos = Asteroids_Utility_GetWindowMiddle();
	difficultyButton = Asteroids_Button_Add_New_Button(200, 100);
	Asteroids_Button_Set_Position(&difficultyButton, pos);
	Asteroids_Difficulty_Menu_Update_ButtonText(&difficultyButton);
	Asteroids_Button_Set_Callback_Button(&Asteroids_Difficulty_Set_NextDifficulty, &difficultyButton);

}

void Asteroids_Difficulty_Menu_Update_ButtonText(Button* button)
{
	float textSize = button->textbox.textSize;
	switch (ASTEROIDS_GAME_DIFFICULTY)
	{
	case EASY:
		Asteroids_Button_Set_Text(&difficultyButton, textSize, "EASY");
	case NORMAL:
		Asteroids_Button_Set_Text(&difficultyButton, textSize, "NORMAL");
	case HARD:
		Asteroids_Button_Set_Text(&difficultyButton, textSize, "HARD");
	default:
		break;
	}
}

void Asteroids_Difficulty_Menu_Update(void)
{
	Asteroids_Difficulty_Menu_Draw();
	Asteroids_Button_Update(&difficultyButton);
}

void Asteroids_Difficulty_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
}

void Asteroids_Difficulty_Set_NextDifficulty(Button* button)
{
	ASTEROIDS_GAME_DIFFICULTY++;
	if (ASTEROIDS_GAME_DIFFICULTY > HARD)
		ASTEROIDS_GAME_DIFFICULTY = EASY;

	Asteroids_Difficulty_Menu_Update_ButtonText(button);
}

