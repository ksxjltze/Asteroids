#pragma once
//---------------------------------------------------------
// file:	final_boss.h
// author:	Bryan Koh Yan Wei
//
//
// email:	yanweibryan.koh@digipen.edu
//			
//
// brief:	Handles the code related to the final boss
//
//
// Copyright  2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "enemy.h"
#include "utility.h"
#include "player.h"
#include "bullet.h"
#include "bigboy.h"
#include "score.h"
#include "game.h"
#include <stdbool.h>


CP_Image Final_Boss_Spawn_Animation;

enum BossState { NO, DEATH, SLEEP, ATTACK, DODGE, BULLET_HELL, ENRAGED};

struct EndGame
{
	bool end;
}game;
	
/*				FINAL_BOSS ENTRY POINT FUNCTIONS							*/
void Asteroids_Final_Boss_Init(void);
void Asteroids_Final_Boss_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[]);
void Asteroids_Enemy_Final_Boss_Spawn(void);
void Asteroids_Final_Boss_Draw(void);


/*				FINAL_BOSS HELPER FUNCTIONS				*/
void Asteroids_Final_Boss_Reset(void);
bool Asteroids_Final_Boss_Summon_Criteria_Check(void);
void Asteroids_Final_Boss_CheckConditions(Enemy* enemy_pool);
float Asteroids_Final_Boss_FireRate(void);
CP_Vector Asteroids_Final_Boss_Get_Position(void);



/*				FINAL BOSS STATE FUNCTIONS				*/
void Asteroids_Final_Boss_State_Update(Player* player, Enemy enemy_pool[], int enemy_count, Bullet bullet_pool[]);
void Asteroids_Final_Boss_State_Manager(void);
void Asteroids_Final_Boss_State_Change_Manager(void);

int Asteroids_Final_Boss_Random_State(int old_id);
void Asteroids_Final_Boss_Shoot(Enemy Final_Boss, Enemy enemy_pool[], Player* player);

void Asteroids_Final_Boss_State_Attack(void* context);
void Asteroids_Final_Boss_State_Idle(void* context);

void Asteroids_Final_Boss_State_Dodge(void* context);
void Asteroids_Final_Boss_Dodge(Enemy* Final_boss, Player* player);

void Asteroids_Final_Boss_State_Enraged(const void* context);
void Asteroids_Final_Boss_Enraged(Enemy* Final_Boss, Player* player);

void Asteroids_Final_Boss_State_BulletHell(void* context);
void Asteroids_Final_Boss_State_Death(const void* context);
void Asteroids_Final_Boss_Idle(Enemy* Final_Boss, Player* player);



/*				FINAL BOSS DRAWING RELATED FUNCTIONS			*/
void Asteroids_Final_Boss_Hp_Draw(Enemy Final_Boss);
void Asteroids_Final_Boss_Death_Screen(Enemy Final_Boss, Player player);


/*				MISCALLENOUS FUNCTIONS				*/
void Asteroids_Continue_Game(void);
void Asteroids_End_Game(void);