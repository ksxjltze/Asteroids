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

struct Bullet arr_bullet[100];
struct Enemy arr_enemy[20];
struct Heart arr_heart[3];
struct powerups arr_powerups[1];
struct Player player;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	settings_setup(WIN_WIDTH, WIN_HEIGHT);
	load_sprites();
	init_entities();
}

//@brief Initializes game entities. Populates entity struct arrays with data (e.g. position, health, etc.)
void init_entities()
{
	//Player
	player = init_player(player, player_width, player_height);

	//TODO: Possibly implement an entity manager to manage different types of entities.
	init_enemies(arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]), enemy_width, enemy_height);
	init_bullets(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), bullet_width, bullet_height);

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
		powerups.pos = generate_random_pos();
		powerups.active = 1;

		powerups.collider.width = powerups_width;
		powerups.collider.height = powerups_height;

		arr_powerups[i] = powerups;

	}

}

//@brief Loads sprites from file path and sets their width and height.
void load_sprites()
{
	player_sprite = CP_Image_Load(PLAYER_SPRITE_PATH);
	bullet_sprite = CP_Image_Load("./Assets/bullet.png");
	enemy_sprite = CP_Image_Load("./Assets/asteroids_cropped.png");
	health_bar_sprite = CP_Image_Load("./Assets/healthbar.png");
	powerups_sprite = CP_Image_Load("./Assets/powerup.png");
	generate_hurt_sprite(enemy_sprite, &enemy_hurt_sprite);
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

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// check input, update simulation, render etc.
	check_input();

	if (shoot_cooldown < 0)
		shoot_cooldown = 0;
	else
		shoot_cooldown -= CP_System_GetDt();

	int enemy_count = sizeof(arr_enemy) / sizeof(arr_enemy[0]);
	process_bullets(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]));
	process_enemies(arr_enemy, enemy_count);
	update_player(&player);

	check_collision_enemy_player(arr_enemy, enemy_count, &player);

	if (player.active != 1)
	{
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
		CP_Engine_Run();
	}

	render();

}

void player_rotate(CP_Vector direction)
{
	CP_Vector vec_up = CP_Vector_Set(0, -1);
	CP_Vector vec_right = CP_Vector_Set(1, 0);
	float dot = CP_Vector_DotProduct(direction, vec_right);

	if (dot >= 0)
		player_rotation = CP_Vector_Angle(direction, vec_up);
	else if (dot < 0)
		player_rotation = -CP_Vector_Angle(direction, vec_up);
}

void check_input()
{
	if (player.active != 1)
		return;

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Vector mousePos = CP_Vector_Set(mouseX, mouseY);
	CP_Vector shoot_direction = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, player.pos));

	player_rotate(shoot_direction);


	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity.y -= speed;
		player.pos.y -= SPEED;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		//velocity.y += speed;
		player.pos.y += SPEED;
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		//velocity.x -= speed;
		player.pos.x -= SPEED;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		//velocity.x += speed;
		player.pos.x += SPEED;
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

void render()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Asteroids", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	display_fps();
	draw_bullets(arr_bullet, sizeof(arr_bullet) / sizeof(arr_bullet[0]), bullet_sprite, bullet_width, bullet_height);
	draw_enemies(arr_enemy, sizeof(arr_enemy) / sizeof(arr_enemy[0]), enemy_sprite, enemy_width, enemy_height, enemy_hurt_sprite, health_bar_sprite);

	// render powerups
	for (int i = 0; i < sizeof(arr_powerups) / sizeof(arr_powerups[0]); i++)
	{
		struct powerups powerups = arr_powerups[i];
		if (powerups.active)
		{
			CP_Image_Draw(powerups_sprite, powerups.pos.x, powerups.pos.y, powerups_width, powerups_height, 255);
		}

	}


	//Draw Hearts
	for (int i = 0; i < player.hp.current; i++)
	{
		if (arr_heart[i].active == 1)
		{
			CP_Image_Draw(player_health_sprite, arr_heart[i].pos.x, arr_heart[i].pos.y, (float)CP_Image_GetWidth(player_health_sprite) * 2,
				(float)CP_Image_GetHeight(player_health_sprite), 255);
		}
	}

	draw_player(player_sprite, player.pos, player_width, player_height, player_rotation);

	//TEST PLAYER ROTATION
	char buf[100];
	_gcvt_s(buf, 100, player_rotation, 4);

	//Display FPS
	CP_Font_DrawText(buf, 300, 100);

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}