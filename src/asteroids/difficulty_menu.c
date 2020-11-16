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
	Asteroids_Button_Set_Callback(&Asteroids_Difficulty_Set_NextDifficulty, &difficultyButton);

	float textSize = 20.0f;
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
	Asteroids_Button_Update(&difficultyButton);
}

void Asteroids_Difficulty_Menu_Draw(void)
{

}

void Asteroids_Difficulty_Set_NextDifficulty(void)
{
	ASTEROIDS_GAME_DIFFICULTY++;
	if (ASTEROIDS_GAME_DIFFICULTY > HARD)
		ASTEROIDS_GAME_DIFFICULTY = EASY;
}

