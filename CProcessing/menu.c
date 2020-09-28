#include "menu.h"
#include "cprocessing.h"
#include "constants.h"

void menu_init(void)
{
	
}

void menu_update(void)
{
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("test", (float)*win_width, (float)*win_height);
}

void menu_exit(void)
{

}