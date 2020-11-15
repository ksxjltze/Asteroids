#pragma once
#include "game.h"
#include "constants.h"
#include "init.h"
#include "enemy.h"
#include "bullet.h"
#include "powerups.h"
#include "player.h"
#include "utility.h"
#include "gameover.h"
#include "pause.h"
#include "particle.h"
#include "user_interface.h"
#include "score.h"
#include "collision_manager.h"
#include <stdbool.h>

#define ASTEROIDS_POOLSIZE_BULLETS 999
#define ASTEROIDS_POOLSIZE_ENEMIES 100

float shoot_cooldown = 0.0f;

CP_Image player_sprite;
CP_Image bullet_sprite;
CP_Image enemy_sprites[2];
CP_Image enemy_hurt_sprites[2];
CP_Image health_bar_sprite;
CP_Image player_health_sprite;

//player
float player_width;
float player_height;
float player_rotation;

float bullet_width;
float bullet_height;

float enemy_width;
float enemy_height;

int debug_mode = 0;

static float difficulty_timer;
extern bool ez_mode = 0;

Bullet bullet_pool[ASTEROIDS_POOLSIZE_BULLETS];
Enemy enemy_pool[ASTEROIDS_POOLSIZE_ENEMIES];
Enemy arr_enemysplit[100];
Player player;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void Asteroids_Init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	Asteroids_Set_Difficulty(ASTEROIDS_GAME_DIFFICULTY);
	Asteroids_Sprites_Load();
	Asteroids_UI_Init();
	Asteroids_Entities_Init();
	Asteroids_Pause_Init();

	particle_init();
	Asteroids_Init_Powerups();
	Asteroids_Init_Score();
	Asteroids_Powerup_Player_Interaction_Init();
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void Asteroids_Update(void)
{
	// check input, update simulation, render etc.
	Asteroids_Check_Input();
	Asteroids_Pause_Update();

	if (!Asteroids_Pause_GetStatus())
	{
		int enemy_count = ASTEROIDS_POOLSIZE_ENEMIES;
		Asteroids_Cooldown_Update();
		Asteroids_Difficulty_Update();
		Asteroids_Enemy_Spawn_Timer(enemy_pool, enemy_count);

		Asteroids_Enemy_Update(enemy_pool, enemy_count, player);
		Asteroids_Bullet_Update(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, enemy_pool, enemy_count);
		Asteroids_Player_Update(&player);

		Asteroids_Collision_CheckCollision_Enemy_Player(enemy_pool, enemy_count, &player);

		particle_update();

		//Gameover
		if (player.active != 1)
		{
			CP_Engine_SetNextGameState(Asteroids_GameOver_Init, Asteroids_GameOver_Update, Asteroids_GameOver_Exit);
			CP_Engine_Run();
		}

		Asteroids_Draw();
		Asteroids_Update_Powerups(&player);

		Asteroids_Debug();
		Asteroids_UI_Update(player);
		Asteroids_Draw_Scores();
	

	}

}

void Asteroids_Cooldown_Update()
{
	if (shoot_cooldown < 0)
		shoot_cooldown = 0;
	else
		shoot_cooldown -= CP_System_GetDt();
}

void Asteroids_Set_Difficulty(DIFFICULTY difficulty)
{
	difficulty_timer = 0;
	ez_mode = 0;
	switch (difficulty)
	{
	case EASY:
		ez_mode = 1;
		break;
	default:
		break;
	}
	ASTEROIDS_GAME_DIFFICULTY = difficulty;
}

void Asteroids_Difficulty_Update()
{
	difficulty_timer += CP_System_GetDt();
	if (difficulty_timer >= ASTEROIDS_DIFFICULTY_INTERVAL)
	{
		Asteroids_Raise_Difficulty();
		difficulty_timer = 0;
	}
}

void Asteroids_Raise_Difficulty()
{
	Asteroids_Enemy_Spawn_Scale_Interval(ASTEROIDS_GAME_DIFFICULTY);
	ASTEROIDS_GAME_DIFFICULTY++;
}

//@brief Initializes game entities. Populates entity struct arrays with data (e.g. position, health, etc.)
void Asteroids_Entities_Init()
{
	//Player
	player = Asteroids_Player_Init(player_width, player_height);

	//TODO: Possibly implement an entity manager to manage different types of entities.
	Asteroids_Enemy_Init(enemy_pool, ASTEROIDS_POOLSIZE_ENEMIES, enemy_width, enemy_height, player);
	Asteroids_Bullet_Init(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, bullet_width, bullet_height);

	//temp
	player.bullet_diameter = bullet_pool[0].collider.diameter;

}

//@brief Loads sprites from file path and sets their width and height.
void Asteroids_Sprites_Load()
{
	player_sprite = CP_Image_Load(PLAYER_SPRITE_PATH);
	bullet_sprite = CP_Image_Load("./Assets/bullet_long.png");

	enemy_sprites[0] = CP_Image_Load("./Assets/asteroids_cropped.png");
	enemy_sprites[1] = CP_Image_Load("./Assets/asteroids_small.png");

	Asteroids_Utility_Generate_Hurt_Sprite(enemy_sprites[0], &enemy_hurt_sprites[0]);
	Asteroids_Utility_Generate_Hurt_Sprite(enemy_sprites[1], &enemy_hurt_sprites[1]);

	player_health_sprite = CP_Image_Load("./Assets/heart.png");

	player.pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	player_width = (float)CP_Image_GetWidth(player_sprite) * 2;
	printf("player width is %f\n", player_width);
	player_height = (float)CP_Image_GetHeight(player_sprite) * 2;
	printf("player height is %f", player_height);

	bullet_width = (float)CP_Image_GetWidth(bullet_sprite);
	bullet_height = (float)CP_Image_GetHeight(bullet_sprite);

	enemy_width = (float)ASTEROIDS_ENEMY_BASE_DIAMETER;
	enemy_height = (float)ASTEROIDS_ENEMY_BASE_DIAMETER;


}

void Asteroids_Player_Rotate(CP_Vector direction)
{
	CP_Vector vec_up = CP_Vector_Set(0, -1);
	CP_Vector vec_right = CP_Vector_Set(1, 0);
	float dot = CP_Vector_DotProduct(direction, vec_right);

	if (dot >= 0)
		player_rotation = CP_Vector_Angle(direction, vec_up);
	else if (dot < 0)
		player_rotation = -CP_Vector_Angle(direction, vec_up);
}

void Asteroids_Check_Input()
{
	Asteroids_Pause_CheckInput();

	if (player.active != 1)
		return;

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Vector mousePos = CP_Vector_Set(mouseX, mouseY);
	CP_Vector shoot_direction = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, player.pos));

	float dt = CP_System_GetDt();

	Asteroids_Player_Rotate(shoot_direction);

	if (CP_Input_KeyDown(KEY_GRAVE_ACCENT))
	{
		if (!debug_mode)
			debug_mode = !debug_mode;
	}

	if (CP_Input_KeyTriggered(KEY_F1))
		debug_mode = !debug_mode;

	if (ez_mode)
		Asteroids_Player_Simple_Movement(&player);
	else
		Asteroids_Player_Check_Input(&player, dt, shoot_direction);

	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		if (shoot_cooldown > 0)
			return;

		shoot_cooldown = 60 / FIRE_RATE; //seconds per bullet
		Asteroids_Bullet_Spawn(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, player, shoot_direction);
		Asteroids_Bullet_Powerup_Split(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, player, shoot_direction);

	}
}

void Asteroids_FPS_Draw()
{
	//Char buffer
	char fps_str[10];
	//Get FPS
	float fps = roundf(CP_System_GetFrameRate());
	sprintf_s(fps_str, 10, "%d", (int)fps); //Convert int to string

	//Display FPS
	CP_Font_DrawText(fps_str, (float)WIN_WIDTH - 100, 100);
}

void Asteroids_Draw() 
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	Asteroids_Bullet_Draw(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS, bullet_sprite, bullet_width, bullet_height);
	Asteroids_Enemy_Draw(enemy_pool, ASTEROIDS_POOLSIZE_ENEMIES, enemy_sprites, enemy_hurt_sprites, enemy_width, enemy_height);
	Asteroids_Player_Draw(player_sprite, player.pos, player_width, player_height, player_rotation);
}

void Asteroids_Debug_Draw_Text()
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	char str_fuel_text[20];
	memset(str_fuel_text, '\0', sizeof(str_fuel_text));

	sprintf_s(str_fuel_text, 20, "Fuel: %d", (int)player.engine.fuel.current);

	CP_Settings_TextSize(50.0f);

	CP_Font_DrawText(str_fuel_text, (float)WIN_WIDTH - 500, 100);
	Asteroids_FPS_Draw();
}

void Asteroids_Debug()
{
	if (!debug_mode)
		return;

	Asteroids_Debug_Draw_Text();
	Asteroids_Debug_Check_Input();
	Asteroids_Player_Debug(player);
	Asteroids_Enemy_Debug(enemy_pool, ASTEROIDS_POOLSIZE_ENEMIES);
	Asteroids_Bullet_Debug(bullet_pool, ASTEROIDS_POOLSIZE_BULLETS);

}

void Asteroids_Debug_Check_Input()
{
	if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		Asteroids_Enemy_Spawn(enemy_pool, ASTEROIDS_POOLSIZE_ENEMIES);
	}

	if (CP_Input_KeyTriggered(KEY_MINUS))
	{
		Asteroids_Player_Death(&player);
	}
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void Asteroids_Exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
	
}