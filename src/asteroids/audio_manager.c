//---------------------------------------------------------
// file:	audio_manager.c
// author:	Lee Jia Keat, Dania Mohd, Liu Ke
// email:	l.jiakeat@digipen.edu
//
// brief:	Audio Manager source file.
//			Manages Audio loaded using the CProcessing Framework.
//			Loads audio files from the Assets folder and provides
//			an Interface to play those sounds.
//			Loads audio on scene enter and frees audio on scene exit.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "audio_manager.h"
#include "cprocessing.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

CP_Sound sfx_ButtonHover; //prev name: sound_ButtonHover
CP_Sound sfx_bgm_MainMenu;
CP_Sound sfx_bullet;
CP_Sound sfx_pickups;
CP_Sound sfx_explosions;
CP_Sound sfx_dangersound;
CP_Sound sfx_gameplaysound;
CP_Image Volbutton;

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
	Volbutton = CP_Image_Load("./Assets/volumebutton.png");

	if (sfx_bgm_MainMenu)
		CP_Sound_PlayAdvanced(sfx_bgm_MainMenu, 0.1f, 1.0f, 1, 0);



}


void Asteroids_Audio_MainMenu_BGM_STOP(void)
{
	//Volbutton = CP_Image_Load("./Assets/volumebutton.png");

	if (sfx_bgm_MainMenu)
		CP_Sound_StopGroup(0);



}

void Asteroids_Audio_Explosion_Play(void)
{
	sfx_explosions = CP_Sound_Load("./Assets/SFX/explosion_sound.mp3");
	CP_Sound_Play(sfx_explosions);
}

void Asteroids_Audio_gameplaysound_Play(void)
{
	sfx_explosions = CP_Sound_Load("./Assets/SFX/gameplaysound.wav");
	CP_Sound_Play(sfx_explosions);
}


void Asteroids_Audio_Gameplay_Play(void)
{
	sfx_gameplaysound = CP_Sound_Load("./Assets/SFX/gameplaysound.wav");
	CP_Sound_Play(sfx_gameplaysound);
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
	sfx_dangersound = CP_Sound_Load("./Assets/SFX/dangeralarm.mp3");
	CP_Sound_Play(sfx_dangersound);
}

void Asteroids_Audio_Manager_Exit(void)
{
	if (sfx_ButtonHover)
		CP_Sound_Free(sfx_ButtonHover);
	if (sfx_bgm_MainMenu)
		CP_Sound_Free(sfx_bgm_MainMenu);
	if (sfx_bullet)
		CP_Sound_Free(sfx_bullet);
	if (sfx_pickups)
		CP_Sound_Free(sfx_pickups);
	if (sfx_explosions)
		CP_Sound_Free(sfx_explosions);
	if (sfx_dangersound)
		CP_Sound_Free(sfx_dangersound);
	if (sfx_gameplaysound)
		CP_Sound_Free(sfx_gameplaysound);
}