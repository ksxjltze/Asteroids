#include "audio_manager.h"
#include "cprocessing.h"

CP_Sound sfx_ButtonHover; //prev name: sound_ButtonHover
CP_Sound sfx_bgm_MainMenu;
CP_Sound sfx_bullet;
CP_Sound sfx_pickups;
CP_Sound sfx_explosions;
CP_Sound sfx_dangersound;

void Asteroids_Audio_Manager_Init(void)
{
	sfx_ButtonHover = CP_Sound_Load("./Assets/HiHat.wav");
	sfx_bgm_MainMenu = CP_Sound_LoadMusic("./Assets/menu_bgm.wav");
}

void Asteroids_Audio_Button_Hover_Play(void)
{
	if (sfx_ButtonHover)
		CP_Sound_Play(sfx_ButtonHover);
}

void Asteroids_Audio_MainMenu_BGM_Play(void)
{
	if (sfx_bgm_MainMenu)
		CP_Sound_PlayAdvanced(sfx_bgm_MainMenu, 0.1f, 1.0f, 1, 0);

}

void Asteroids_Audio_Explosion_Play(void)
{
	sfx_explosions = CP_Sound_Load("./Assets/SFX/explosion_sound.wav");
	CP_Sound_Play(sfx_explosions);
}

void Asteroids_Audio_Bullets_Play(void)
{
	sfx_bullet = CP_Sound_Load("./Assets/SFX/laser.wav");
	CP_Sound_Play(sfx_bullet);
}
void Asteroids_Audio_PickUps_Play(void)
{
	sfx_pickups = CP_Sound_Load("./Assets/SFX/powerup.wav");
	CP_Sound_Play(sfx_pickups);
}

void Asteroids_Audio_dangersound_Play(void)
{
	sfx_pickups = CP_Sound_load("./Assets/SFX/dangeralarm.wav");
	CP_Sound_Play(sfx_dangersound);
}

void Asteroids_Audio_Manager_Exit(void)
{
	CP_Sound_Free(sfx_ButtonHover);
	CP_Sound_Free(sfx_bgm_MainMenu);
	CP_Sound_Free(sfx_bullet);
}
