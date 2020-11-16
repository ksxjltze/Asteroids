#include "skin_menu.h"
#include "cprocessing.h"
#include "utility.h"
#include "button.h"
#include "constants.h"

typedef struct Skins
{
	CP_Image sprite;
	const char* name;
	float cost;
}Skin;

enum PLAYER_SKINS { DEFAULT, LEGACY, PROTOTYPE};
static int current_skinID;

static Skin current_skin;
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

}

void Asteroids_Skin_Menu_Update(void)
{
	Asteroids_Button_Update(&Btn_NextSkin);
	Asteroids_Skin_Menu_Draw();
}

void Asteroids_Skin_Menu_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(current_skin.sprite, skinDisplayPos.x, skinDisplayPos.y, ASTEROIDS_PLAYER_SPRITE_WIDTH * displayScaleFactor, ASTEROIDS_PLAYER_SPRITE_HEIGHT * displayScaleFactor, 255);

}

void Asteroids_Skin_Menu_Next_Skin(void)
{
	current_skinID++;
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
	}

	if (current_skinID >= PROTOTYPE)
	{
		current_skinID = -1;
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