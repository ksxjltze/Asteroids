#pragma once
#include "cprocessing.h" //CProcessing Framework, used to Render sprites and perform game logic (e.g. Vectors)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Used to seed rand() function for random number generation.
#include "init.h"
#include "enemy.h"
#include "bullet.h"

void game_init(void);
void game_update(void);
void game_exit(void);
void render();
int display_splash();
void check_input();
void draw_player();
void process_bullets();
int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2);
CP_Vector generate_random_pos();
CP_Image generate_hurt_sprite(CP_Image sprite);
void load_sprites();
void init_entities();