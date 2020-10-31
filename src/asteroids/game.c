#pragma once
#include "game.h"
#include "constants.h"

float shoot_cooldown = 0.0f;

CP_Image player_sprite;
CP_Image bullet_sprite;
CP_Image enemy_sprite;
CP_Image enemy_hurt_sprite;
CP_Image health_bar_sprite;
CP_Image player_health_sprite;
CP_Image powerups_sprite;

//player
float player_width;
float player_height;
float player_rotation;

float bullet_width;
float bullet_height;

float enemy_width;
float enemy_height;

float powerups_width;
float powerups_height;

int difficulty = 0; //NORMAL
int debug_mode = 0;

struct Bullet arr_bullet[999];
struct Enemy arr_enemy[20];
struct Heart arr_heart[3];
struct powerups arr_powerups[1];
struct Player player;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void Asteroids_Init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	Asteroids_Settings_Setup(WIN_WIDTH, WIN_HEIGHT);
	Asteroids_Sprites_Load();
	Asteroids_Entities_Init();
	Asteroids_Pause_Init();
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
		Asteroids_Cooldown_Update();

		int enemy_count = sizeof(arr_enemy) / sizeof(arr_enemy[0]);
		Asteroids_Bullet_Update(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]));
		Asteroids_Enemy_Update(arr_enemy, enemy_count);
		Asteroids_Player_Update(&player);
		Asteroids_Collision_CheckCollision_Enemy_Player(arr_enemy, enemy_count, &player);

		//Gameover
		if (player.active != 1)
		{
			CP_Engine_SetNextGameState(Asteroids_GameOver_Init, Asteroids_GameOver_Update, Asteroids_GameOver_Exit);
			CP_Engine_Run();
		}

		Asteroids_Draw();
		Asteroids_Debug();

	}

}

void Asteroids_Cooldown_Update()
{
	if (shoot_cooldown < 0)
		shoot_cooldown = 0;
	else
		shoot_cooldown -= CP_System_GetDt();
}

//@brief Initializes game entities. Populates entity struct arrays with data (e.g. position, health, etc.)
void Asteroids_Entities_Init()
{
	//Player
	player = Asteroids_Player_Init(player_width, player_height);

	//TODO: Possibly implement an entity manager to manage different types of entities.
	Asteroids_Enemy_Init(arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]), enemy_width, enemy_height);
	Asteroids_Bullet_Init(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), bullet_width, bullet_height);

	for (int i = 0; i < sizeof(arr_heart) / sizeof(arr_heart[0]); i++)
	{
		//
		struct Heart heart = arr_heart[i];
		heart.pos = CP_Vector_Set((i+1) * 100.0f, 50.0f);
		heart.active = 1;

		arr_heart[i] = heart;

	}

	for (int i = 0; i < sizeof(arr_powerups) / sizeof(arr_powerups[0]); i++)
	{
		struct powerups powerups = arr_powerups[i];
		powerups.pos = Asteroids_Utility_Generate_Random_Pos();
		powerups.active = 1;

		powerups.collider.width = powerups_width;
		powerups.collider.height = powerups_height;

		arr_powerups[i] = powerups;

	}

}

//@brief Loads sprites from file path and sets their width and height.
void Asteroids_Sprites_Load()
{
	player_sprite = CP_Image_Load(PLAYER_SPRITE_PATH);
	bullet_sprite = CP_Image_Load("./Assets/bullet.png");
	enemy_sprite = CP_Image_Load("./Assets/asteroids_cropped.png");
	Asteroids_Utility_Generate_Hurt_Sprite(enemy_sprite, &enemy_hurt_sprite);
	player_health_sprite = CP_Image_Load("./Assets/heart.png");

	player.pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	player_width = (float)CP_Image_GetWidth(player_sprite) * 2;
	player_height = (float)CP_Image_GetHeight(player_sprite) * 2;

	bullet_width = (float)CP_Image_GetWidth(bullet_sprite);
	bullet_height = (float)CP_Image_GetHeight(bullet_sprite);

	enemy_width = (float)CP_Image_GetWidth(enemy_sprite) * 0.1f;
	enemy_height = (float)CP_Image_GetHeight(enemy_sprite) * 0.1f;

	powerups_width = (float)CP_Image_GetWidth(powerups_sprite) * 0.3f;
	powerups_height = (float)CP_Image_GetWidth(powerups_sprite) * 0.3f;
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

	Asteroids_Player_Rotate(shoot_direction);

	if (CP_Input_KeyDown(KEY_GRAVE_ACCENT))
	{
		if (!debug_mode)
			debug_mode = !debug_mode;
	}

	if (CP_Input_KeyReleased(KEY_GRAVE_ACCENT))
	{
		if (debug_mode)
			debug_mode = !debug_mode;
	}

	if (CP_Input_KeyTriggered(KEY_F1))
		debug_mode = !debug_mode;
	

	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity.y -= speed;
		player.pos.y -= player.speed;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		//velocity.y += speed;
		player.pos.y += player.speed;
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		//velocity.x -= speed;
		player.pos.x -= player.speed;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		//velocity.x += speed;
		player.pos.x += player.speed;
	}

	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		if (shoot_cooldown > 0)
			return;

		shoot_cooldown = 60 / FIRE_RATE; //seconds per bullet

		for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
		{
			struct Bullet bullet = arr_bullet[i];
			if (!bullet.active) {
				bullet.pos = CP_Vector_Set(player.pos.x, player.pos.y);
				bullet.velocity = CP_Vector_Set(shoot_direction.x * BULLET_SPEED, shoot_direction.y * BULLET_SPEED);
				bullet.active = 1;

				arr_bullet[i] = bullet;
				break;
			}
		}

	}
}

void display_fps()
{
	//Char buffer
	char fps_str[10];
	//Get FPS
	float fps = roundf(CP_System_GetFrameRate());
	sprintf_s(fps_str, 10, "%d", (int)fps); //Convert int to string

	//Display FPS
	CP_Font_DrawText(fps_str, 100, 100);
}

void Asteroids_Draw()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Asteroids", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	display_fps();
	Asteroids_Bullet_Draw(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), bullet_sprite, bullet_width, bullet_height);
	Asteroids_Enemy_Draw(arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]), enemy_sprite, enemy_width, enemy_height, enemy_hurt_sprite, health_bar_sprite);

	Asteroids_Player_Draw(player_sprite, player.pos, player_width, player_height, player_rotation);

	//TEST PLAYER ROTATION
	char str_rotation[10];

	char str_fuel[10];
	char* str_fuel_label = "Fuel: ";

	char str_fuel_text[20];
	memset(str_fuel_text, '\0', sizeof(str_fuel_text));

	_gcvt_s(str_rotation, 10, player_rotation, 4);
	sprintf_s(str_fuel, 10, "%d", (int)player.engine.fuel.current);

	strcat_s(str_fuel_text, sizeof(str_fuel_text), str_fuel_label);
	strcat_s(str_fuel_text, sizeof(str_fuel_text), str_fuel);
	CP_Font_DrawText(str_fuel_text, 500, 100);
	
	//Display FPS
	CP_Font_DrawText(str_rotation, 300, 100);

}

void Asteroids_Debug()
{
	if (!debug_mode)
		return;

	Asteroids_Player_Debug(player);
	Asteroids_Enemy_Debug(arr_enemy, sizeof(arr_enemy)/sizeof(arr_enemy[0]));
	Asteroids_Bullet_Debug(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]));

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void Asteroids_Exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}