#include "help.h"
#include "utility.h"
#include "button.h"
#include "main_menu.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 100
#define BTN_TEXTSIZE 75

Help_screen screen;

#define LAST_PAGE 3
enum Page_Num {PAGE_1 = 1, PAGE_2, PAGE_3, PAGE_4 };

CP_Image Page_Image[LAST_PAGE];

Button BackBtn, NextBtn, ExitBtn;

void Asteroids_Help_Screen_Init(void)
{
	for (int i = 0; i < LAST_PAGE; i++)
	{
		Page_Image[i] = CP_Image_Load("./Assets/Control_screen%d", i);
	}

	screen.id = PAGE_1;
	screen.width = (float)CP_System_GetWindowWidth();
	screen.height = (float)CP_System_GetWindowHeight();
	screen.pos = Asteroids_Utility_GetWindowMiddle();
	screen.Image = Page_Image[screen.id];


	Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);

	Asteroids_Button_Set_Text(&BackBtn, BTN_TEXTSIZE, "Back");
	Asteroids_Button_Set_Text(&NextBtn, BTN_TEXTSIZE, "Next");
	Asteroids_Button_Set_Text(&ExitBtn, BTN_TEXTSIZE, "Exit");

	CP_Vector position_offset = Asteroids_Utility_GetWindowMiddle();

	CP_Vector BackBtnPos = CP_Vector_Set(0 + BUTTON_WIDTH / 2, position_offset.y - BUTTON_HEIGHT / 2);
	CP_Vector ExitBtnPos = CP_Vector_Set(position_offset.x - BUTTON_WIDTH / 2, (float)CP_System_GetWindowHeight() - BUTTON_HEIGHT / 2);
	CP_Vector NextBtnPos = CP_Vector_Set((float)CP_System_GetWindowWidth() - BUTTON_WIDTH / 2, position_offset.y - BUTTON_HEIGHT / 2);

	Asteroids_Button_Set_Position(&BackBtn, BackBtnPos);
	Asteroids_Button_Set_Position(&NextBtn, NextBtnPos);
	Asteroids_Button_Set_Position(&ExitBtn, ExitBtnPos);

	Asteroids_Button_Set_Callback_Button(Asteroids_Help_Screen_Exit_ToMenu, &ExitBtn);
	Asteroids_Button_Set_Callback_Button(Asteroids_Help_Screen_IncreasePageNo, &NextBtn);
	Asteroids_Button_Set_Callback_Button(Asteroids_Help_Screen_DecreasePageNo, &BackBtn);


}
void Asteroids_Help_Screen_Update(void)
{
	if (screen.id != PAGE_1)
		Asteroids_Button_Update(&BackBtn);
	if (screen.id != LAST_PAGE)
		Asteroids_Button_Update(&NextBtn);

	Asteroids_Draw_Screen_Page();
	Asteroids_Help_Screen_UpdatePageNo();
	Asteroids_Button_Update(&ExitBtn);
}
void Asteroids_Help_Screen_Exit(void)
{

}

void Asteroids_Help_Screen_Exit_ToMenu(void)
{
	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
}

void Asteroids_Draw_Screen_Page(void)
{

	CP_Image_Draw(Page_Image[screen.id], screen.pos.x, screen.pos.y, screen.width, screen.height, 255);
}

void Asteroids_Help_Screen_IncreasePageNo(void)
{
	screen.id += 1;
}

void Asteroids_Help_Screen_DecreasePageNo(void)
{
	screen.id -= 1;
}
