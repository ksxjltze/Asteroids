//---------------------------------------------------------
// file:	gameover.h
// author:	Lee Jia Keat
// contributors: Bryan Koh Yan Wei (Display score)
// email:	l.jiakeat@digipen.edu, 
// brief:	Game Over scene header file, handles the game over scene.
//			Displays the player's score (Asteroids destroyed and time survived)
//			and provides buttons to retry the game or exit to title screen.
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "constants.h"
#include "main_menu.h"
#include "init.h"

//JIA KEAT
void Asteroids_GameOver_Init(void);
void Asteroids_GameOver_Update(void);
void Asteroids_GameOver_Exit(void);

void Asteroids_GameOver_Restart(void);
void Asteroids_GameOver_Quit(void);

//BRYAN
void Asteroids_GameOver_Init_Score(void);
void Asteroids_GameOver_Display_Score(void);