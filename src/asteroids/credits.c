#include "credits.h"
#include "button.h"
#include "main_menu.h"

enum CREDUTS_SCREEN {page1, page2, page3 };

#define btnWidth 200
#define btnHeight 75
#define btnText 75
creditsScreen overlay;
Button nextBtn, exitBtn, backBtn;

void Asteroids_Credits_Screen_Init(void)
{
	for (unsigned int i = 0; i < MAXPAGE; i++)
	{
		char Path[100];
		sprintf_s(Path, 100, "./Assets/Credits/credits%d.png", i);
		overlay.page[i] = CP_Image_Load(Path);
	}

	overlay.ID = 0;
	overlay.width = (float)CP_System_GetWindowWidth();
	overlay.height = (float)CP_System_GetWindowHeight();
	overlay.pos = Asteroids_Utility_GetWindowMiddle();

	Asteroids_Audio_Manager_Init();
	Asteroids_Credits_Screen_ButtonInit();
}
void Asteroids_Credits_Screen_ButtonInit(void)
{
	nextBtn = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	backBtn = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);
	exitBtn = Asteroids_Button_Add_New_Button(btnWidth, btnHeight);

	Asteroids_Button_Set_Text(&backBtn, btnText, "Back");
	Asteroids_Button_Set_Text(&nextBtn, btnText, "Next");
	Asteroids_Button_Set_Text(&exitBtn, btnText, "Exit");

	Asteroids_Button_Set_Callback_Void(Asteroids_Credits_Screen_ExitToMenu, &exitBtn);
	Asteroids_Button_Set_Callback_Void(Asteroids_Credits_Screen_NextPage, &nextBtn);
	Asteroids_Button_Set_Callback_Void(Asteroids_Credits_Screen_PreviousPage, &backBtn);

	CP_Vector position_offset = Asteroids_Utility_GetWindowMiddle();

	CP_Vector exitBtnPos = CP_Vector_Set(position_offset.x - btnWidth / 2, (float)WIN_HEIGHT - btnHeight);
	CP_Vector backBtnPos = CP_Vector_Set(0, position_offset.y - btnHeight / 2);
	CP_Vector nextBtnPos = CP_Vector_Set((float)WIN_WIDTH - btnWidth, position_offset.y - btnHeight / 2);

	Asteroids_Button_Set_Position(&backBtn, backBtnPos);
	Asteroids_Button_Set_Position(&nextBtn, nextBtnPos);
	Asteroids_Button_Set_Position(&exitBtn, exitBtnPos);
}

void Asteroids_Credits_Screen_Update(void)
{
	Asteroids_Credits_Screen_Draw();

	Asteroids_Button_Update(&exitBtn);
	if(overlay.ID != MAXPAGE - 1)
		Asteroids_Button_Update(&nextBtn);
	if(overlay.ID != page1)
		Asteroids_Button_Update(&backBtn);
}
void Asteroids_Credits_Screen_Exit(void)
{

}

void Asteroids_Credits_Screen_NextPage(void)
{
	overlay.ID += 1;

}
void Asteroids_Credits_Screen_PreviousPage(void)
{
	overlay.ID -= 1;
}
void Asteroids_Credits_Screen_ExitToMenu(void)
{
	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
}

void Asteroids_Credits_Screen_Draw(void)
{
	CP_Image_DrawAdvanced(overlay.page[overlay.ID], overlay.pos.x, overlay.pos.y, overlay.width, overlay.height, 255, 0);
}