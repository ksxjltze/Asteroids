#include "difficulty_menu.h"
#include "button.h"
#include "utility.h"
#include "constants.h"
#include "file_manager.h"

static Button difficultyButton;
static CP_Vector middle;

void Asteroids_Difficulty_Menu_Init(void)
{
	middle = Asteroids_Utility_GetWindowMiddle();
	CP_Vector pos = middle;
	difficultyButton = Asteroids_Button_Add_New_Button(300, 100);
	pos.x -= difficultyButton.width / 2;
	pos.y = WIN_HEIGHT * 0.5f;

	Asteroids_Button_Set_Position(&difficultyButton, pos);
	Asteroids_Difficulty_Get_From_File();
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
		break;
	case IMPOSSIBLE:
		Asteroids_Button_Set_Text(button, textSize, "IMPOSSIBLE");
		break;
	default:
		break;
	}

}

void Asteroids_Difficulty_Menu_Display_Info(void)
{
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	switch (DIFFICULTY_OPTION)
	{
	case EASY:
		CP_Font_DrawText("Movement: Simple", middle.x - 200, middle.y - 200);
		CP_Font_DrawText("Perk: Split Bullets", middle.x - 200, middle.y - 150);
		break;
	case NORMAL:
		CP_Font_DrawText("Movement: Simple", middle.x - 200, middle.y - 200);
		break;
	case HARD:
		CP_Font_DrawText("Movement: Acceleration", middle.x - 200, middle.y - 200);
		CP_Font_DrawText("Automatic Deceleration", middle.x - 200, middle.y - 150);
		break;
	case INSANE:
		CP_Font_DrawText("Movement: Acceleration", middle.x - 200, middle.y - 200);
		CP_Font_DrawText("Manual Deceleration", middle.x - 200, middle.y - 150);
		break;
	case IMPOSSIBLE:
		CP_Font_DrawText("Movement: Acceleration", middle.x - 200, middle.y - 200);
		CP_Font_DrawText("Manual Deceleration", middle.x - 200, middle.y - 150);
		CP_Font_DrawText("Asteroid Collision: Disabled", middle.x - 200, middle.y - 100);
		break;
	}
}

void Asteroids_Difficulty_Menu_Update(void)
{
	Asteroids_Difficulty_Menu_Draw();
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Current Difficulty:", difficultyButton.position.x + difficultyButton.width / 2, difficultyButton.position.y - 20);
	Asteroids_Button_Update(&difficultyButton);
	Asteroids_Difficulty_Menu_Display_Info();
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void Asteroids_Difficulty_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
}

void Asteroids_Difficulty_Set_NextDifficulty(Button* button)
{
	DIFFICULTY_OPTION++;
	if (DIFFICULTY_OPTION > IMPOSSIBLE)
		DIFFICULTY_OPTION = EASY;

	Asteroids_Difficulty_Save_To_File();
	Asteroids_Difficulty_Menu_Update_ButtonText(button);

}

void Asteroids_Difficulty_Save_To_File(void)
{
	FILE* settingsFile = Asteroids_Open_File("./Assets/settings.data", "w");
	if (settingsFile)
	{
		fprintf(settingsFile, "%d", DIFFICULTY_OPTION);
		Asteroids_Close_File(settingsFile);
	}
}

void Asteroids_Difficulty_Get_From_File(void)
{
	FILE* settingsFile = Asteroids_Open_File("./Assets/settings.data", "r");
	if (settingsFile)
	{
		int read = fscanf_s(settingsFile, "%d", &DIFFICULTY_OPTION);
		printf("Read %d values from file.\n", read);
		Asteroids_Close_File(settingsFile);
	}
}