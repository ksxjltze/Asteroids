//---------------------------------------------------------
// file:	main_menu.c
// author:	Bryan Koh Yan Wei
// contributors: Lee Jia Keat (Difficulty, Skin, Leaderboard and Upgrade Menus), Liu Ke (UI Design)
// email:	yanweibryan.koh@digipen.edu, l.jiakeat@digipen.edu, ke.liu@digipen.edu
//
// brief:	Main menu source file.
//			Handles Initialization, Updating and Drawing of the Main Menu/Title Screen.
//			Contains functions to display other sub menus (overlays) as well as buttons to toggle them.
//			Is the entry point into the main game, as well as the screen where settings such as difficulty can be set from.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "main_menu.h"
#include "difficulty_menu.h"
#include "skin_menu.h"
#include "upgrades_menu.h"
#include "currency.h"
#include "audio_manager.h"
#include "leaderboard.h"
#include <stdbool.h>
#include "guide.h"
#include "credits.h"

#define BUTTON_WIDTH 400.0f
#define BUTTON_HEIGHT 100.0f

bool mainMenu;
static int overlay_type;

bool Playmusic = true;

bool page1;
bool page2;

enum OVERLAY_TYPE { CREDITS_SCREEN, LEADERBOARD_SCREEN, GUIDE_SCREEN, DIFFICULTY_MENU, SKIN_MENU, UPGRADES_MENU, VOL_BUTTON};

DIFFICULTY ASTEROIDS_GAME_DIFFICULTY = NORMAL;
DIFFICULTY DIFFICULTY_OPTION = NORMAL;

static CP_Color backgroundColor;
static CP_Color textColor;
static float menuTextSize;
static char* menuText = "Asteroids";

Button Credits, Play, Quit, Leaderboard, Guide, ExitBtn, DifficultyBtn, SkinsBtn, NextPage, PrevPage, UpgradesBtn, VolumeBtn, FullscreenBtn;
CP_Image Control_screen;
CP_Image Control_screen2;
CP_Image Credits_screen;
CP_Image Chosenship;
CP_Image volumeBtnImage;

CP_Image backgroundImage;

CP_Vector backgroundPos;
CP_Vector backgroundPos2;
CP_Vector backgroundPos3;

static CP_Sound bgm;

void Asteroids_MainMenu_Init(void)
{
	mainMenu = true;
	page1 = true;
	page2 = false;

	Asteroids_Menu_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);
	volumeBtnImage = CP_Image_Load("./Assets/volumebutton.png");
	Asteroids_MainMenu_Button_Init();
	Credits_screen = CP_Image_Load("./Assets/credits.png");

	backgroundImage = CP_Image_Load("./Assets/background.png");
	backgroundPos = Asteroids_Utility_GetWindowMiddle();
	backgroundPos2 = backgroundPos;
	backgroundPos3 = backgroundPos2;

	backgroundPos2.x = backgroundPos.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;
	backgroundPos3.x = backgroundPos2.x + (float)WIN_WIDTH - ASTEROIDS_MAINMENU_BACKGROUND_SCROLL_OFFSET;

	menuText = "Asteroids";
	backgroundColor = CP_Color_Create(0, 0, 0, 255);
	textColor = CP_Color_Create(255, 255, 255, 255);
	menuTextSize = 100.0f;

	Asteroids_Currency_Init();
	Asteroids_Upgrades_Init();
	Asteroids_Skin_Menu_Init();
	Asteroids_Audio_Manager_Init();
	Asteroids_Audio_MainMenu_BGM_Play();

	current_skin.sprite = CP_Image_Load("./Assets/final_boss1.png");
}


void Asteroids_MainMenu_Update(void)
{
	CP_Settings_Background(backgroundColor);
	Asteroids_MainMenu_Update_Background();
	Asteroids_Draw_MainMenu();
	
}

void Asteroids_MainMenu_Exit(void)
{
	Asteroids_Audio_Manager_Exit();
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

void Asteroids_MainMenu_Draw_Background(CP_Image image)
{
	if (!mainMenu)
		return;

	CP_Image_Draw(image, backgroundPos.x, backgroundPos.y, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);
	CP_Image_Draw(image, backgroundPos2.x, backgroundPos2.y, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);
	CP_Image_Draw(image, backgroundPos3.x, backgroundPos3.y, (float)WIN_WIDTH, (float)WIN_HEIGHT, 255);

}

void Asteroids_Draw_MainMenu(void)
{
	Asteroids_MainMenu_Draw_Background(backgroundImage);
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(textColor);
	CP_Settings_TextSize(menuTextSize);

	if (mainMenu)
	{
		CP_Font_DrawTextBox(menuText, 0, 50.0f + menuTextSize / 2, (float)WIN_WIDTH);
		Asteroids_Button_Update(&Play);
		Asteroids_Button_Update(&Guide);
		Asteroids_Button_Update(&Credits);
		Asteroids_Button_Update(&Leaderboard);
		Asteroids_Button_Update(&Quit);
		Asteroids_Button_Update(&DifficultyBtn);
		Asteroids_Button_Update(&SkinsBtn);
		Asteroids_Button_Update(&UpgradesBtn);
		Asteroids_Button_Update(&VolumeBtn);
		Asteroids_Button_Update(&FullscreenBtn);
		Asteroids_MainMenu_Draw_Current_Ship(); 
		Asteroids_Upgrades_Menu_Display_Balance(CP_Color_Create(255, 255, 255, 255), CP_Vector_Set(120, 30));
	}
	else if (!mainMenu)
	{
		Asteroids_MainMenu_CheckInput();
		Asteroids_Button_Update(&ExitBtn);
	}
}

void Asteroids_MainMenu_Draw_Current_Ship()
{
	CP_Vector position = (CP_Vector){ (float)WIN_WIDTH / 2.0f, (float)WIN_HEIGHT / 2.0f };
	CP_Image_DrawAdvanced(current_skin.sprite, position.x, position.y , 5 * ASTEROIDS_PLAYER_SPRITE_WIDTH, 5 * ASTEROIDS_PLAYER_SPRITE_HEIGHT, 255, Asteroids_MainMenu_Rotation_Towards_Mouse());

}

float Asteroids_MainMenu_Rotation_Towards_Mouse()
{
	return Asteroids_Utility_Get_Rotation_Angle_To_Mouse(Asteroids_Utility_GetWindowMiddle());
}

void Asteroids_MainMenu_Button_Init(void)
{
	float textSize = 45.0f;

	float x1 = 0;
	float x2 = (float)(WIN_WIDTH - BUTTON_WIDTH);

	float y2 = (float)((float)WIN_HEIGHT / 2 - (BUTTON_HEIGHT / 2)); // middle 
	float y1 = y2 - BUTTON_HEIGHT;
	float y3 = y2 + BUTTON_HEIGHT;

	// Main Menu Button
	CP_Vector pos1 = CP_Vector_Set(x1 , y1); // Play button
	CP_Vector pos2 = CP_Vector_Set(x1, y2+50); // guide button
	CP_Vector pos3 = CP_Vector_Set(x1, y3+100); // credits button
	CP_Vector pos4 = CP_Vector_Set(x2, y1); // leaderboard button
	CP_Vector pos5 = CP_Vector_Set(x2, y2+50); // skins buttton
	CP_Vector pos10 = CP_Vector_Set(x2, y3+100); // Prev page || quit
	CP_Vector pos11 = CP_Vector_Set(x1 + 50, 0.065f * WIN_HEIGHT); //vol button

	// Exit Button
	CP_Vector pos6 = CP_Vector_Set((float)(((float)WIN_WIDTH / 2 - BUTTON_WIDTH / 2)), (float)(WIN_HEIGHT - BUTTON_HEIGHT));

	// Difficulty Button
	CP_Vector pos7 = CP_Vector_Set((float)WIN_WIDTH - 300 , 50);
	CP_Vector upgradesPos = CP_Vector_Set((float)WIN_WIDTH -300 , 125);
	CP_Vector fullscreenPos = CP_Vector_Set(0 , 0.175f * WIN_HEIGHT);

	// Control screen buttons
	CP_Vector pos8 = CP_Vector_Set((float)WIN_WIDTH - BUTTON_WIDTH, (float)(WIN_HEIGHT / 2)); // Next Page
	CP_Vector pos9 = CP_Vector_Set(0, (float)(WIN_HEIGHT / 2)); // Prev page

	Play = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Guide = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Credits = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Leaderboard = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	Quit = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	ExitBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	DifficultyBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH - 100.0f , BUTTON_HEIGHT - 40.0f);
	SkinsBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	NextPage = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	PrevPage = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
	UpgradesBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH - 100.0f , BUTTON_HEIGHT - 40.0f);
	VolumeBtn = Asteroids_Button_Add_New_Image_Button(volumeBtnImage, 75 , 75);
	FullscreenBtn = Asteroids_Button_Add_New_Button(200, 50);

	Asteroids_Button_Set_Text(&Play, textSize, "Play");
	Asteroids_Button_Set_Text(&Guide, textSize, "Guide");
	Asteroids_Button_Set_Text(&Credits, textSize, "Credits");
	Asteroids_Button_Set_Text(&Leaderboard, textSize, "Leaderboard");
	Asteroids_Button_Set_Text(&Quit, textSize, "Quit");
	Asteroids_Button_Set_Text(&ExitBtn, textSize, "Exit");
	Asteroids_Button_Set_Text(&DifficultyBtn, textSize, "Difficulty");
	Asteroids_Button_Set_Text(&SkinsBtn, textSize, "Skins");
	Asteroids_Button_Set_Text(&NextPage, textSize, "Next");
	Asteroids_Button_Set_Text(&PrevPage, textSize, "Back");
	Asteroids_Button_Set_Text(&UpgradesBtn, textSize, "Upgrades");
	Asteroids_Button_Set_Text(&VolumeBtn, textSize, "Vol");
	Asteroids_Button_Set_Text(&FullscreenBtn, 35, "Fullscreen");


	Asteroids_Button_Set_Position(&Play, pos1 );
	Asteroids_Button_Set_Position(&Guide, pos2);
	Asteroids_Button_Set_Position(&Credits, pos3);
	Asteroids_Button_Set_Position(&Leaderboard, pos4);
	Asteroids_Button_Set_Position(&Quit, pos10);
	Asteroids_Button_Set_Position(&ExitBtn, pos6);
	Asteroids_Button_Set_Position(&DifficultyBtn, pos7);
	Asteroids_Button_Set_Position(&NextPage, pos8);
	Asteroids_Button_Set_Position(&PrevPage, pos9);
	Asteroids_Button_Set_Position(&SkinsBtn, pos5);
	Asteroids_Button_Set_Position(&UpgradesBtn, upgradesPos);
	Asteroids_Button_Set_Position(&VolumeBtn, pos11);
	Asteroids_Button_Set_Position(&FullscreenBtn, fullscreenPos);

	Asteroids_Button_Set_Callback_Void(&Asteroids_Play_Game, &Play);
	Asteroids_Button_Set_Callback_Void(&Asteroids_MainMenu_Guide, &Guide);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Credits_Enter, &Credits);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Display_LeaderBoard, &Leaderboard);
	Asteroids_Button_Set_Callback_Void(&Asteroids_QuitGame, &Quit);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Exit_Screen, &ExitBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Menu_Display_DifficultyMenu, &DifficultyBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Menu_Display_SkinMenu, &SkinsBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Menu_Display_UpgradesMenu, &UpgradesBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_Menu_Display_VolumeONOFF, &VolumeBtn);
	Asteroids_Button_Set_Callback_Void(&Asteroids_MainMenu_Set_FullScreen, &FullscreenBtn);


	DifficultyBtn.colors.idle = CP_Color_Create(255, 255, 0, 255);
	Asteroids_Button_Set_Text_Colors(&DifficultyBtn, CP_Color_Create(0, 0, 0, 255));

	UpgradesBtn.colors.idle = CP_Color_Create(255, 0, 0, 255);
	Asteroids_Button_Set_Text_Colors(&UpgradesBtn, CP_Color_Create(255, 255, 255, 255));
}

void Asteroids_Menu_Display_UpgradesMenu(void)
{
	mainMenu = false;
	overlay_type = UPGRADES_MENU;
	Asteroids_Upgrades_Menu_Init();
}

// Turning BGM vol on and off
void Asteroids_Menu_Display_VolumeONOFF(void)
{
	if (Playmusic == false)
	{
		Asteroids_Audio_MainMenu_BGM_Play();
		
	}
	else
	{
		Asteroids_Audio_MainMenu_BGM_Pause();
	}

}

void Asteroids_Menu_Display_SkinMenu(void)
{
	mainMenu = false;
	overlay_type = SKIN_MENU;
}

void Asteroids_Menu_Display_DifficultyMenu(void)
{
	mainMenu = false;
	overlay_type = DIFFICULTY_MENU;
	Asteroids_Difficulty_Menu_Init();
}

void Asteroids_Play_Game(void)
{
	CP_Engine_SetNextGameState(Asteroids_Init, Asteroids_Update, Asteroids_Exit);
} 

void Asteroids_QuitGame(void)
{
	CP_Engine_Terminate();
}

void Asteroids_Credits_Enter(void)
{
	CP_Engine_SetNextGameState(Asteroids_Credits_Screen_Init, Asteroids_Credits_Screen_Update, Asteroids_Credits_Screen_Exit);
}

void Asteroids_Display_LeaderBoard(void)
{
	overlay_type = LEADERBOARD_SCREEN;
	mainMenu = false;
	Asteroids_Leaderboard_Init();

}
void Asteroids_MainMenu_Guide(void)
{	
	CP_Engine_SetNextGameState(Asteroids_Help_Screen_Init, Asteroids_Help_Screen_Update, Asteroids_Help_Screen_Exit);
}

void Asteroids_Exit_Screen(void)
{
	overlay_type = 0;
	mainMenu = true;

	Asteroids_Audio_MainMenu_BGM_Play();

	if (overlay_type == LEADERBOARD_SCREEN)
	{
		Asteroids_Leaderboard_Exit();
	}
}

void Asteroids_MainMenu_CheckInput(void)
{
	switch (overlay_type)
	{
		case CREDITS_SCREEN:
			Asteroids_Credits_Enter();
			break;
		case LEADERBOARD_SCREEN:
			Asteroids_Leaderboard_Update();
			break;
		case GUIDE_SCREEN:
			Asteroids_MainMenu_Guide();
			break;
		case DIFFICULTY_MENU:
			Asteroids_Difficulty_Menu_Update();
			break;
		case SKIN_MENU:
			Asteroids_Skin_Menu_Update();
			break;
		case UPGRADES_MENU:
			Asteroids_Upgrades_Menu_Update();
	}
}

void Asteroids_MainMenu_Set_FullScreen()
{
	if (FULLSCREEN)
	{
		WIN_WIDTH = DEFAULT_WIN_WIDTH;
		WIN_HEIGHT = DEFAULT_WIN_HEIGHT;
		CP_System_SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
		FULLSCREEN = 0;
	}
	else
	{
		CP_System_Fullscreen();
		WIN_WIDTH = CP_System_GetWindowWidth();
		WIN_HEIGHT = CP_System_GetWindowHeight();
		FULLSCREEN = 1;
	}
	Asteroids_MainMenu_Exit();
	Asteroids_MainMenu_Init();
}