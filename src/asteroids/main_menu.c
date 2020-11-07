#include "main_menu.h"

#define BUTTON_WIDTH 200.0f
#define BUTTON_HEIGHT 50.0f

bool status;
static int input;

Button Credits, Play, Quit, Leaderboard, Controls, Exit;

void Asteroids_MainMenu_Init(void)
{
	status = true;
	Asteroids_Menu_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);
	Asteroids_MainMenu_Button_Init();
}

void Asteroids_MainMenu_Update(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	Asteroids_Draw_MainMenu();
	//CP_Settings_TextSize(100.0f);
	//CP_Font_DrawText("CLICK ANYWHERE TO START", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	//if (CP_Input_MouseClicked())
	//{
	//	CP_Engine_SetNextGameState(Asteroids_Init, Asteroids_Update, Asteroids_Exit);
	//	CP_Engine_Run();
	//}

}

void Asteroids_MainMenu_Exit(void)
{

}

void Asteroids_Draw_MainMenu(void)
{
	if (status)
	{
		Asteroids_Button_Update(&Play);
		Asteroids_Button_Update(&Controls);
		Asteroids_Button_Update(&Credits);
		Asteroids_Button_Update(&Leaderboard);
		Asteroids_Button_Update(&Quit);
	}
	else
		Asteroids_MainMenu_CheckInput();

}

void Asteroids_MainMenu_Button_Init(void)
{
	float textSize = 30.0f;

	float x1 = (float)((WIN_WIDTH / 2) - (BUTTON_WIDTH / 2));
	float x2 = (float)((WIN_WIDTH / 2) + (BUTTON_WIDTH / 2));

	float y2 = (float)(WIN_HEIGHT / 2 - (BUTTON_HEIGHT / 2)); // middle 
	float y1 = y2 - BUTTON_HEIGHT;
	float y3 = y2 + BUTTON_HEIGHT;

	CP_Vector pos1 = CP_Vector_Set(x1, y1);
	CP_Vector pos2 = CP_Vector_Set(x1, y2);
	CP_Vector pos3 = CP_Vector_Set(x1, y3);
	CP_Vector pos4 = CP_Vector_Set(x2, y1);
	CP_Vector pos5 = CP_Vector_Set(x2, y2);

	CP_Vector pos6 = CP_Vector_Set((float)(WIN_WIDTH / 2), (float)(WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2));

	Play = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Controls = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Credits = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Leaderboard = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Quit = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Exit = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);

	Asteroids_Button_Set_Text(&Play, textSize, "Play");
	Asteroids_Button_Set_Text(&Controls, textSize, "Controls");
	Asteroids_Button_Set_Text(&Credits, textSize, "Credits");
	Asteroids_Button_Set_Text(&Leaderboard, textSize, "Leaderboard");
	Asteroids_Button_Set_Text(&Quit, textSize, "Quit");
	Asteroids_Button_Set_Text(&Exit, textSize, "Exit");

	Asteroids_Button_Set_Position(&Play, pos1);
	Asteroids_Button_Set_Position(&Controls, pos2);
	Asteroids_Button_Set_Position(&Credits, pos3);
	Asteroids_Button_Set_Position(&Leaderboard, pos4);
	Asteroids_Button_Set_Position(&Quit, pos5);
	Asteroids_Button_Set_Position(&Exit, pos6);

	Asteroids_Button_Set_Callback(&Asteroids_Play_Game, &Play);
	Asteroids_Button_Set_Callback(&Asteroids_Controls, &Controls);
	Asteroids_Button_Set_Callback(&Asteroids_Credits, &Credits);
	Asteroids_Button_Set_Callback(&Asteroids_LeaderBoard, &Leaderboard);
	Asteroids_Button_Set_Callback(&Asteroids_QuitGame, &Quit);
	Asteroids_Button_Set_Callback(&Asteroids_Exit_Screen, &Exit);
}

void Asteroids_Play_Game(void)
{
	CP_Engine_SetNextGameState(Asteroids_Init, Asteroids_Update, Asteroids_Exit);
} 


void Asteroids_QuitGame(void)
{
	CP_Engine_Terminate();
}

void Asteroids_Credits(void)
{
	input = 1;
	printf("input is %d\n", input);
	status = false;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Credits (TODO)", 0.0f, (float)(WIN_HEIGHT / 2), (float)WIN_WIDTH);

	Asteroids_Button_Update(&Exit);
}

void Asteroids_LeaderBoard(void)
{
	input = 2;
	printf("input is %d\n", input);
	status = false;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("LeaderBoard (TODO)", 0.0f, (float)(WIN_HEIGHT / 2), (float)WIN_WIDTH);

	Asteroids_Button_Update(&Exit);
}
void Asteroids_Controls(void)
{	
	input = 3;
	printf("input is %d\n", input);
	status = false;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawTextBox("Controls (TODO)", 0.0f, (float)(WIN_HEIGHT / 2), (float)WIN_WIDTH);

	Asteroids_Button_Update(&Exit);
}

void Asteroids_Exit_Screen(void)
{
	input = 0;
	status = true;
}

void Asteroids_MainMenu_CheckInput(void)
{
	switch (input)
	{
			
		case 1:
			Asteroids_Credits();
			break;
		case 2:
			Asteroids_LeaderBoard();
			break;
		case 3:
			Asteroids_Controls();
			break;
	}
}