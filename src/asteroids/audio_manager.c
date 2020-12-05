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

CP_Sound sfx_ButtonHover; //prev name: sound_ButtonHover
CP_Sound sfx_bgm_MainMenu;
CP_Sound sfx_bullet;
CP_Sound sfx_pickups;
CP_Sound sfx_explosions;
CP_Sound sfx_dangersound;
CP_Sound sfx_gameplaysound;
CP_Sound sfx_EZCLAP;
CP_Sound bgm_BossBattle;

CP_Image VOLbutton;

static int clapCount = 0;
static float clapTimer = 0.0f;

enum Asteroids_Sound_Group {MUSIC};
enum Asteroids_Music_ID { BGM_BOSS_BATTLE };

void Asteroids_Audio_Manager_Init(void)
{
	sfx_ButtonHover = CP_Sound_Load("./Assets/HiHat.wav");
	sfx_bgm_MainMenu = CP_Sound_LoadMusic("./Assets/menu_bgm.wav");
	sfx_EZCLAP = CP_Sound_Load("./Assets/Clap.wav");
	bgm_BossBattle = CP_Sound_Load("./Assets/bossBattle.wav");

	clapCount = 0;
	clapTimer = 0.0f;
}

void Asteroids_Audio_Button_Hover_Play(void)
{
	if (sfx_ButtonHover)
		CP_Sound_Play(sfx_ButtonHover);
}

void Asteroids_Audio_Manager_Start_Music(int id)
{
	switch(id)
	{
	case BGM_BOSS_BATTLE:
		if (bgm_BossBattle)
			CP_Sound_PlayAdvanced(bgm_BossBattle, 70.0f, 1.0f, 1, MUSIC);
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

void Asteroids_Audio_MainMenu_BGM_Play(void)
{
	VOLbutton = CP_Image_Load("./Assets/volumebutton.png");

	if (sfx_bgm_MainMenu)
		CP_Sound_PlayAdvanced(sfx_bgm_MainMenu, 0.1f, 1.0f, 1, MUSIC);
}


void Asteroids_Audio_MainMenu_BGM_STOP(void)
{
	VOLbutton = CP_Image_Load("./Assets/volumebutton.png");

	if (sfx_bgm_MainMenu)
		CP_Sound_StopGroup(MUSIC);

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
	CP_Sound_PlayAdvanced(sfx_gameplaysound, 0.1f ,0.1f, 1, 0);
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
	CP_Sound_Free(sfx_ButtonHover);
	CP_Sound_Free(sfx_bgm_MainMenu);
	CP_Sound_Free(sfx_bullet);
	CP_Sound_Free(sfx_EZCLAP);
	CP_Sound_Free(bgm_BossBattle);
}

void Asteroids_Audio_EZCLAP_Play(void)
{
	clapTimer += CP_System_GetDt();
	if (clapTimer > 0.5f && clapCount < 10)
	{
		CP_Sound_PlayAdvanced(sfx_EZCLAP, 20.0f, CP_Random_RangeFloat(0.6f, 1.5f), 1, 9);
		clapTimer = 0;
		clapCount++;
	}
}
