#pragma once
#include "cprocessing.h"
#include "collider_circle.h"
#include "utility.h"
#include <stdbool.h>
#include <stdio.h>
#include"player.h"
#include "powerups.h"


// GENERAL
void Asteroids_Powerup_Player_Interaction_Init(void);

// DRAWING OF INTERACTION
void Asteroids_Powerup_Player_Invulernability(Player* player);
void Asteroids_Powerup_Lifespan_Manager(void);