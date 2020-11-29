#include "audio_manager.h"
#include "cprocessing.h"

CP_Sound sound_ButtonHover;
CP_Sound bgm_MainMenu;

void Asteroids_Audio_Manager_Init(void)
{
	sound_ButtonHover = CP_Sound_Load("./Assets/HiHat.wav");
	bgm_MainMenu = CP_Sound_LoadMusic("./Assets/menu_bgm.wav");
}

void Asteroids_Audio_Button_Hover_Play(void)
{
	if (sound_ButtonHover)
		CP_Sound_Play(sound_ButtonHover);
}

void Asteroids_Audio_MainMenu_BGM_Play(void)
{
	if(bgm_MainMenu)
		CP_Sound_PlayMusic(bgm_MainMenu);
}

void Asteroids_Audio_Manager_Exit(void)
{
	CP_Sound_Free(sound_ButtonHover);
	CP_Sound_Free(bgm_MainMenu);
}