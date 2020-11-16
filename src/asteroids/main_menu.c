#include "main_menu.h"

#define BUTTON_WIDTH 200.0f
#define BUTTON_HEIGHT 50.0f

bool status;
static int input;

bool page1;
bool page2;

DIFFICULTY ASTEROIDS_GAME_DIFFICULTY = NORMAL;
static CP_Color backgroundColor;
static CP_Color textColor;
static float menuTextSize;
static char* menuText = "Asteroids";

Button Credits, Play, Quit, Leaderboard, Controls, Exit, EzButton, NextPage, PrevPage;
CP_Image Control_screen;
CP_Image Control_screen2;
CP_Image Credits_screen;

CP_Image backgroundImage;

CP_Vector backgroundPos;
CP_Vector backgroundPos2;
CP_Vector backgroundPos3;

void Asteroids_MainMenu_Init(void)
{
	status = true;
	page1 = true;
	page2 = false;

	Asteroids_Menu_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);
	Asteroids_MainMenu_Button_Init();
	Control_screen = CP_Image_Load("./Assets/Control_screen.png");
	Control_screen2 = CP_Image_Load("./Assets/Control_screen2.png");
	Credits_screen = CP_Image_Load("./Assets/credits.png");

	backgroundImage = CP_Image_Load("./Assets/starfield.png");
	backgroundPos = Asteroids_Utility_GetWindowMiddle();
	backgroundPos2 = backgroundPos;
	backgroundPos3 = backgroundPos2;

	backgroundPos2.x = backgroundPos.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;
	backgroundPos3.x = backgroundPos2.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;

	if (ASTEROIDS_GAME_DIFFICULTY == EASY)
	{
		backgroundColor = CP_Color_Create(255, 255, 0, 255);
		textColor = CP_Color_Create(255, 0, 255, 255);
		menuText = "aStErOiDs";
		menuTextSize = 300.0f;
		return;
	}

	menuText = "Asteroids";
	backgroundColor = CP_Color_Create(0, 0, 0, 255);
	textColor = CP_Color_Create(255, 255, 255, 255);
	menuTextSize = 100.0f;
}

void Asteroids_MainMenu_Update(void)
{
	CP_Settings_Background(backgroundColor);
	Asteroids_MainMenu_Update_Background();
	Asteroids_Draw_MainMenu();
}

void Asteroids_MainMenu_Exit(void)
{

}

void Asteroids_MainMenu_Update_Background(void)
{
	float dt = CP_System_GetDt();
	float offset = (float)WIN_WIDTH / 2;

	backgroundPos.x -= dt * ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_SPEED;
	backgroundPos2.x -= dt * ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_SPEED;
	backgroundPos3.x -= dt * ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_SPEED;

	if (backgroundPos.x + offset < 0)
		backgroundPos.x = backgroundPos3.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;

	if (backgroundPos2.x + offset < 0)
		backgroundPos2.x = backgroundPos.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;

	if (backgroundPos3.x + offset < 0)
		backgroundPos3.x = backgroundPos2.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;

}

void Asteroids_MainMenu_Draw_Background(void)
{
	if (!status)
		return;

	CP_Image_Draw(backgroundImage, backgroundPos.x, backgroundPos.y, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);
	CP_Image_Draw(backgroundImage, backgroundPos2.x, backgroundPos2.y, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);
	CP_Image_Draw(backgroundImage, backgroundPos3.x, backgroundPos3.y, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);

}

void Asteroids_Draw_MainMenu(void)
{
	Asteroids_MainMenu_Draw_Background();
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(textColor);
	CP_Settings_TextSize(menuTextSize);
	CP_Font_DrawTextBox(menuText, 0, 50.0f + menuTextSize / 2, (float)WIN_WIDTH);

	if (status)
	{
		Asteroids_Button_Update(&Play);
		Asteroids_Button_Update(&Controls);
		Asteroids_Button_Update(&Credits);
		Asteroids_Button_Update(&Leaderboard);
		Asteroids_Button_Update(&Quit);
		Asteroids_Button_Update(&EzButton);
	}
	else if (!status)
	{
		Asteroids_MainMenu_CheckInput();
		Asteroids_Button_Update(&Exit);
	}

}

void Asteroids_MainMenu_Button_Init(void)
{
	float textSize = 40.0f;

	float x1 = (float)((WIN_WIDTH / 2) - BUTTON_WIDTH);
	float x2 = (float)(WIN_WIDTH / 2);

	float y2 = (float)(WIN_HEIGHT / 2 - (BUTTON_HEIGHT / 2)); // middle 
	float y1 = y2 - BUTTON_HEIGHT;
	float y3 = y2 + BUTTON_HEIGHT;

	// Main Menu Button
	CP_Vector pos1 = CP_Vector_Set(x1, y1);
	CP_Vector pos2 = CP_Vector_Set(x1, y2);
	CP_Vector pos3 = CP_Vector_Set(x1, y3);
	CP_Vector pos4 = CP_Vector_Set(x2, y1);
	CP_Vector pos5 = CP_Vector_Set(x2, y2);

	// Exit Button
	CP_Vector pos6 = CP_Vector_Set((float)((WIN_WIDTH / 2 - BUTTON_WIDTH / 2)), (float)(WIN_HEIGHT - BUTTON_HEIGHT));

	// EZ MODE Button
	CP_Vector pos7 = CP_Vector_Set((float)WIN_WIDTH - 200, 50);

	// Control screen buttons
	CP_Vector pos8 = CP_Vector_Set((float)WIN_WIDTH - BUTTON_WIDTH, (float)(WIN_HEIGHT / 2)); // Next Page
	CP_Vector pos9 = CP_Vector_Set(0, (float)(WIN_HEIGHT / 2)); // Prev page

	Play = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Controls = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Credits = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Leaderboard = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Quit = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Exit = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	EzButton = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	NextPage = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	PrevPage = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);

	Asteroids_Button_Set_Text(&Play, textSize, "Play");
	Asteroids_Button_Set_Text(&Controls, textSize, "Help");
	Asteroids_Button_Set_Text(&Credits, textSize, "Credits");
	Asteroids_Button_Set_Text(&Leaderboard, textSize, "Leaderboard");
	Asteroids_Button_Set_Text(&Quit, textSize, "Quit");
	Asteroids_Button_Set_Text(&Exit, textSize, "Exit");
	Asteroids_Button_Set_Text(&EzButton, textSize, "Ez Mode");
	Asteroids_Button_Set_Text(&NextPage, textSize, "Next");
	Asteroids_Button_Set_Text(&PrevPage, textSize, "Back");

	Asteroids_Button_Set_Position(&Play, pos1);
	Asteroids_Button_Set_Position(&Controls, pos2);
	Asteroids_Button_Set_Position(&Credits, pos3);
	Asteroids_Button_Set_Position(&Leaderboard, pos4);
	Asteroids_Button_Set_Position(&Quit, pos5);
	Asteroids_Button_Set_Position(&Exit, pos6);
	Asteroids_Button_Set_Position(&EzButton, pos7);
	Asteroids_Button_Set_Position(&NextPage, pos8);
	Asteroids_Button_Set_Position(&PrevPage, pos9);

	Asteroids_Button_Set_Callback(&Asteroids_Play_Game, &Play);
	Asteroids_Button_Set_Callback(&Asteroids_Controls, &Controls);
	Asteroids_Button_Set_Callback(&Asteroids_Credits, &Credits);
	Asteroids_Button_Set_Callback(&Asteroids_LeaderBoard, &Leaderboard);
	Asteroids_Button_Set_Callback(&Asteroids_QuitGame, &Quit);
	Asteroids_Button_Set_Callback(&Asteroids_Exit_Screen, &Exit);
	Asteroids_Button_Set_Callback(&Asteroids_Menu_Set_Difficulty, &EzButton);
}

void Asteroids_Menu_Set_Difficulty(void)
{
	if (ASTEROIDS_GAME_DIFFICULTY == NORMAL)
	{
		ASTEROIDS_GAME_DIFFICULTY = EASY;

		backgroundColor = CP_Color_Create(255, 255, 0, 255);
		textColor = CP_Color_Create(255, 0, 255, 255);
		menuText = "EZ EZ EZ";
		menuTextSize = 300.0f;
	}
	else
	{
		ASTEROIDS_GAME_DIFFICULTY = NORMAL;
		backgroundColor = CP_Color_Create(0, 0, 0, 255);
		textColor = CP_Color_Create(255, 255, 255, 255);
		menuText = "Asteroids";
		menuTextSize = 100.0f;
	}

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
	status = false;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(Credits_screen, (float)(WIN_WIDTH / 2), (float)(WIN_HEIGHT / 2), (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 20));
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Ty for carry", (float)(WIN_WIDTH / 2 + 350.0f), (float)(WIN_HEIGHT * 0.28));
	Asteroids_Button_Update(&Exit);
}

void Asteroids_LeaderBoard(void)
{
	input = 2;
	status = false;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Font_DrawTextBox("LeaderBoard (TODO)", 0.0f, (float)(WIN_HEIGHT / 2), (float)WIN_WIDTH);

}
void Asteroids_Controls(void)
{	
	input = 3;
	status = false;

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Vector pos8 = CP_Vector_Set((float)WIN_WIDTH - BUTTON_WIDTH, (float)(WIN_HEIGHT / 2)); // Next Page
	CP_Vector pos9 = CP_Vector_Set(0, (float)(WIN_HEIGHT / 2)); // Prev page
	CP_Vector mouse;
	mouse.x = CP_Input_GetMouseX();
	mouse.y = CP_Input_GetMouseY();

	if(page1)
	{
		CP_Image_Draw(Control_screen, (float)WIN_WIDTH / 2.0f, (float)WIN_HEIGHT / 2.0f, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);
		Asteroids_Button_Update(&NextPage);
		if (mouse.x >= pos8.x && mouse.x <= pos8.x + BUTTON_WIDTH && 
			mouse.y >= pos8.y && mouse.y <= pos8.y + BUTTON_HEIGHT)
		{
			if (CP_Input_MouseClicked())
			{
				page1 = false;
				page2 = true;
			}
		}
	}
	if (page2)
	{
		CP_Image_Draw(Control_screen2, (float)WIN_WIDTH / 2.0f, (float)WIN_HEIGHT / 2.0f, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);
		Asteroids_Button_Update(&PrevPage);
		if (mouse.x >= pos9.x && mouse.x <= pos9.x + BUTTON_WIDTH &&
			mouse.y >= pos9.y && mouse.y <= pos9.y + BUTTON_HEIGHT)
		{
			if (CP_Input_MouseClicked())
			{
				page1 = true;
				page2 = false;
			}
		}
	}

}

void Asteroids_Exit_Screen(void)
{
	input = 0;
	// Draw main menu screen. 
	status = true;

	//Reset control page display to first page
	page1 = true;
	page2 = false;
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