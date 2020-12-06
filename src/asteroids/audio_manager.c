//---------------------------------------------------------
// file:	enemy.c
// author:	Lee Jia Keat
// contributors: Dania Mohd (Bullet sound, buttons), Liu Ke (explosions, dangeralert gameplay BGM)
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Enemy entity source file.
//			Initializes, Updates and Draws Enemy entities (Asteroid).
//			Provides an interface for damaging, destroying and spawning enemies.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "audio_manager.h"
#include "cprocessing.h"

#define SFX_VOL 0.6f
#define BGM_VOL 3.0f

CP_Sound sfx_ButtonHover; //prev name: sound_ButtonHover
CP_Sound sfx_bgm_MainMenu;
CP_Sound sfx_bullet;
CP_Sound sfx_pickups;
CP_Sound sfx_explosions;
CP_Sound sfx_dangersound;
CP_Sound sfx_gameplaysound;
CP_Sound sfx_EZCLAP;
CP_Sound bgm_BossBattle;
CP_Sound bgm_Credits;
CP_Sound bgm_GameOver;
CP_Sound bgm_Shop;

CP_Image VOLbutton;

static int clapCount = 0;
static float clapTimer = 0.0f;

enum Asteroids_Sound_Group {MUSIC, SFX};
enum Asteroids_Music_ID { BGM_BOSS_BATTLE, BGM_CREDITS, BGM_GAMEOVER, BGM_SHOP};

void Asteroids_Audio_Manager_Init(void)
{
	sfx_ButtonHover = CP_Sound_Load("./Assets/HiHat.wav");
	//sfx_bgm_MainMenu = CP_Sound_LoadMusic("./Assets/BGM/menu_bgm.wav");
	sfx_bgm_MainMenu = CP_Sound_LoadMusic("./Assets/BGM/bgm_main_menu.wav");
	sfx_EZCLAP = CP_Sound_Load("./Assets/Clap.wav");
	bgm_BossBattle = CP_Sound_Load("./Assets/BGM/bossBattle.wav");
	bgm_Credits = CP_Sound_Load("./Assets/BGM/credits_bgm.wav");
	bgm_GameOver = CP_Sound_Load("./Assets/BGM/gg.wav");
	bgm_Shop = CP_Sound_Load("./Assets/BGM/shopMusic.wav");
	sfx_explosions = CP_Sound_Load("./Assets/SFX/explosion_sound.mp3");
	sfx_gameplaysound = CP_Sound_Load("./Assets/SFX/gameplaysound.wav");
	sfx_bullet = CP_Sound_Load("./Assets/SFX/laser.wav");
	sfx_pickups = CP_Sound_Load("./Assets/SFX/powerup.wav");
	sfx_dangersound = CP_Sound_Load("./Assets/SFX/dangeralarm.mp3");

	clapCount = 0;
	clapTimer = 0.0f;
}

void Asteroids_Audio_Manager_BGM_GameOver_Play()
{
	Asteroids_Audio_Manager_Start_Music(BGM_GAMEOVER);
}

void Asteroids_Audio_Manager_BGM_Credits_Play()
{
	Asteroids_Audio_Manager_Start_Music(BGM_CREDITS);
}

void Asteroids_Audio_Button_Hover_Play(void)
{
	if (sfx_ButtonHover)
		CP_Sound_Play(sfx_ButtonHover);
}

void Asteroids_Audio_Manager_Start_Music(int id)
{
	CP_Sound_StopGroup(MUSIC);
	switch(id)
	{
	case BGM_BOSS_BATTLE:
		if (bgm_BossBattle)
			CP_Sound_PlayAdvanced(bgm_BossBattle, BGM_VOL + 1.5f, 1.0f, 1, MUSIC);
		break;
	case BGM_CREDITS:
		if (bgm_Credits)
			CP_Sound_PlayAdvanced(bgm_Credits, BGM_VOL - 1.5f, 1.0f, 1, MUSIC);
		break;
	case BGM_GAMEOVER:
		if (bgm_GameOver)
			CP_Sound_PlayAdvanced(bgm_GameOver, BGM_VOL, 1.0f, 1, MUSIC);
		break;
	case BGM_SHOP:
		if (bgm_Shop)
			CP_Sound_PlayAdvanced(bgm_Shop, BGM_VOL, 1.0f, 1, MUSIC);
		break;
	}
}

void Asteroids_Audio_Manager_Stop_Music()
{
	CP_Sound_StopGroup(MUSIC);
}

void Asteroids_Audio_Manager_BGM_Boss_Battle_Play()
{
	Asteroids_Audio_Manager_Start_Music(BGM_BOSS_BATTLE);
}

void Asteroids_Audio_Manager_BGM_Shop_Play()
{
	Asteroids_Audio_Manager_Start_Music(BGM_SHOP);
}

void Asteroids_Audio_MainMenu_BGM_Play(void)
{
	CP_Sound_StopGroup(MUSIC);
	VOLbutton = CP_Image_Load("./Assets/volumebutton.png");

	if (sfx_bgm_MainMenu)
		CP_Sound_PlayAdvanced(sfx_bgm_MainMenu, 0.8f, 1.0f, 1, MUSIC);
}


void Asteroids_Audio_MainMenu_BGM_Pause(void)
{
	static int isPlaying = 1;
	if (isPlaying)
	{
		isPlaying = 0;
		CP_Sound_PauseGroup(MUSIC);
	}
	else
	{
		isPlaying = 1;
		CP_Sound_ResumeGroup(MUSIC);
	}

}

void Asteroids_Audio_Explosion_Play(void)
{
	if (sfx_explosions)
		CP_Sound_PlayAdvanced(sfx_explosions, 0.1f, 1.0f, 0, SFX);
}

void Asteroids_Audio_Gameplay_Play(void)
{
	if (sfx_gameplaysound)
		CP_Sound_PlayAdvanced(sfx_gameplaysound, SFX_VOL, 1.0f, 0, SFX);
}

void Asteroids_Audio_Bullets_Play(void)
{
	if (sfx_bullet)
		CP_Sound_PlayAdvanced(sfx_bullet, SFX_VOL, 1.0f, 0, SFX);
}
void Asteroids_Audio_PickUps_Play(void)
{
	if(sfx_pickups)
		CP_Sound_PlayAdvanced(sfx_pickups, SFX_VOL, 1.0f, 0, SFX);
}

void Asteroids_Audio_dangersound_Play(void)
{
	if (sfx_dangersound)
		CP_Sound_PlayAdvanced(sfx_dangersound, SFX_VOL, 1.0f, 0, SFX);
}

void Asteroids_Audio_Manager_Exit(void)
{
	CP_Sound_Free(sfx_ButtonHover);
	CP_Sound_Free(sfx_bgm_MainMenu);
	CP_Sound_Free(sfx_bullet);
	CP_Sound_Free(sfx_explosions);
	CP_Sound_Free(sfx_EZCLAP);
	CP_Sound_Free(sfx_dangersound);
	CP_Sound_Free(sfx_pickups);
	CP_Sound_Free(sfx_gameplaysound);
	CP_Sound_Free(bgm_BossBattle);
	CP_Sound_Free(bgm_Credits);
	CP_Sound_Free(bgm_GameOver);
	CP_Sound_Free(bgm_Shop);
}

void Asteroids_Audio_EZCLAP_Play(void)
{
	clapTimer += CP_System_GetDt();
	if (clapTimer > 0.5f && clapCount < 10)
	{
		CP_Sound_PlayAdvanced(sfx_EZCLAP, 20.0f, CP_Random_RangeFloat(0.6f, 1.5f), 1, MUSIC);
		clapTimer = 0;
		clapCount++;
	}
}
