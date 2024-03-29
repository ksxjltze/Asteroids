//---------------------------------------------------------
// file:	skin_menu.c
// author:	Lee Jia Keat
// contributors: Liu Ke (Additional Skins)
// email:	l.jiakeat@digipen.edu, ke.liu@digipen.edu
//
// brief:	Skin menu source file.
//			Handles Initialization, Loading, Selecting and Saving of skins.
//			Reads and Writes from a specific file to read and save player skins.
//			Displays a user interface for swapping skins.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "skin_menu.h"
#include "utility.h"
#include "button.h"
#include "constants.h"
#include "file_manager.h"

enum PLAYER_SKINS { DEFAULT, LEGACY, PROTOTYPE, skin2, skin3, skin4, skin5};
static int current_skinID;

Skin current_skin;
static CP_Vector skinDisplayPos;
static CP_Vector Btn_NextSkin_Pos;

static float displayScaleFactor;
static Button Btn_NextSkin;

void Asteroids_Skin_Menu_Init(void)
{
	current_skin.sprite = NULL;
	current_skin.name = "NULL";
	current_skin.cost = 0;
	current_skinID = -1;

	Asteroids_Skin_Menu_Load_Default();

	skinDisplayPos = Asteroids_Utility_GetWindowMiddle();
	displayScaleFactor = 3.0f;

	Btn_NextSkin = Asteroids_Button_Add_New_Button(200, 50);
	Btn_NextSkin_Pos = CP_Vector_Set((float)WIN_WIDTH / 2 - Btn_NextSkin.width / 2, (float)WIN_HEIGHT * 0.7f);
	Asteroids_Button_Set_Position(&Btn_NextSkin, Btn_NextSkin_Pos);
	Asteroids_Button_Set_Text(&Btn_NextSkin, 30.0f, "Next Skin");
	Asteroids_Button_Set_Callback_Void(&Asteroids_Skin_Menu_Next_Skin, &Btn_NextSkin);

	Asteroids_Skin_Menu_Read_Selected_Skin();

}

void Asteroids_Skin_Menu_Update(void)
{
	Asteroids_Button_Update(&Btn_NextSkin);
	Asteroids_Skin_Menu_Draw();
}

// function to draw out the skin menu
void Asteroids_Skin_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(current_skin.name, 0.5f * WIN_WIDTH, 0.25f * WIN_HEIGHT);
	CP_Image_Draw(current_skin.sprite, skinDisplayPos.x, skinDisplayPos.y, ASTEROIDS_PLAYER_SPRITE_WIDTH * displayScaleFactor, ASTEROIDS_PLAYER_SPRITE_HEIGHT * displayScaleFactor, 255);

}

//function to select next skin

void Asteroids_Skin_Menu_Next_Skin(void)
{
	current_skinID++;
	Asteroids_Skin_Menu_Load_Selected_Skin();
	Asteroids_Skin_Menu_Write_Selected_Skin();

	if (current_skinID >= skin5)
	{
		current_skinID = -1;
	}
}

//list of skins installed in the assets folders

void Asteroids_Skin_Menu_Load_Selected_Skin()
{
	switch (current_skinID)
	{
	case DEFAULT:
		Asteroids_Skin_Menu_Load_Default();
		break;
	case LEGACY:
		Asteroids_Skin_Menu_Load_Skin(ASTEROIDS_PLAYER_SPRITE_PATH_LEGACY, "Legacy", 0);
		break;
	case PROTOTYPE:
		Asteroids_Skin_Menu_Load_Skin(ASTEROIDS_PLAYER_SPRITE_PATH_PROTOTYPE, "Prototype", 0);
		break;
	case skin2:
		Asteroids_Skin_Menu_Load_Skin("./Assets/spaceship3.png", "skin2", 0);
		break;
	case skin3:
		Asteroids_Skin_Menu_Load_Skin("./Assets/spaceship4.png", "skin3", 0);
		break;
	case skin4:
		Asteroids_Skin_Menu_Load_Skin("./Assets/spaceship5.png", "skin4", 0);
		break;
	case skin5:
		Asteroids_Skin_Menu_Load_Skin("./Assets/spaceship6.png", "skin5", 0);
		break;

	}
}

void Asteroids_Skin_Menu_Load_Skin(const char* path, const char* skin_name, float cost)
{
	current_skin.sprite = CP_Image_Load(path);
	current_skin.name = skin_name;
	current_skin.cost = cost;
}

void Asteroids_Skin_Menu_Load_Default(void)
{
	current_skinID = DEFAULT;
	Asteroids_Skin_Menu_Load_Skin(ASTEROIDS_PLAYER_SPRITE_PATH_DEFAULT, "Default", 0);
}

void Asteroids_Skin_Menu_Read_Selected_Skin()
{
	FILE* skinsFile = Asteroids_Open_File("./Assets/skins.data", "r");
	if (skinsFile)
	{
		fscanf_s(skinsFile, "%d", &current_skinID);
		Asteroids_Skin_Menu_Load_Selected_Skin(current_skinID);
		Asteroids_Close_File(skinsFile);
	}
	return;
}

void Asteroids_Skin_Menu_Write_Selected_Skin()
{
	FILE* skinsFile = Asteroids_Open_File("./Assets/skins.data", "w");
	if (skinsFile)
	{
		fprintf_s(skinsFile, "%d", current_skinID);
		Asteroids_Close_File(skinsFile);
	}
	return;

}