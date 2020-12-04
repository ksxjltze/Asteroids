//---------------------------------------------------------
// file:	audio_manager.h
// author:	Lee Jia Keat, Dania Mohd, Liu Ke
// email:	l.jiakeat@digipen.edu
//
// brief:	Audio Manager header file.
//			Manages Audio loaded using the CProcessing Framework.
//			Loads audio files from the Assets folder and provides
//			an Interface to play those sounds.
//			Loads audio on scene enter and frees audio on scene exit.
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include <stdbool.h>
void Asteroids_Audio_Manager_Init(void);
void Asteroids_Audio_Button_Hover_Play(void);
void Asteroids_Audio_MainMenu_BGM_Play(void);
void Asteroids_Audio_Manager_Exit(void);
void Asteroids_Audio_Bullets_Play(void);
void Asteroids_Audio_PickUps_Play(void);
void Asteroids_Audio_dangersound_Play(void);
void Asteroids_Audio_Explosion_Play(void);
void Asteroids_Audio_gameplaysound_Play(void);
void Asteroids_Audio_MainMenu_BGM_STOP(void);