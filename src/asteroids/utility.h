#pragma once
//---------------------------------------------------------
// file:	utility.h
// author:	Lee Jia Keat
//
// email:	l.jiakeat@digipen.edu, 
//
// brief:	Utility file which contains helper functions used often in the code base.
//			
// 
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include <stdlib.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "constants.h"
#include "enemy.h"

CP_Vector Asteroids_Utility_Generate_Random_Pos();
CP_Vector Asteroids_Utility_Generate_Random_Pos_Var2(float width, float height);
CP_Vector Asteroids_Utility_GetWindowMiddle();
CP_Vector Asteroids_Utility_Find_Closest_Enemy(Enemy enemy_pool[], Player* player);
void Asteroids_Utility_Generate_Hurt_Sprite(CP_Image sprite, CP_Image* out);
void Asteroids_Utility_Generate_Blue_Sprite(CP_Image sprite, CP_Image* out);
bool isMouseOver_Rect(CP_Vector position, float width, float height, float mouseX, float mouseY);
bool Asteroids_Utility_isInWindow(CP_Vector position);
void Asteroids_Utility_Move_Object_To_Mouse(CP_Vector* position);
void Asteroids_Utility_Move_Object_To_Mouse_Stationary(CP_Vector* position, CP_Vector* velocity);
float Asteroids_Utility_Get_Rotation_Angle_To_Mouse(CP_Vector position);