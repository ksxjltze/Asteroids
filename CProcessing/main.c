//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h" //CProcessing Framework, used to Render sprites and perform game logic (e.g. Vectors)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Used to seed rand() function for random number generation.

struct Collider_AABB {
	int width;
	int height;
};

struct Bullet {
	CP_Vector pos;
	struct Collider_AABB collider;
	CP_Vector velocity;
	int active;
};

struct Health {
	float current;
	float max;
};

struct Enemy {
	CP_Vector pos;
	struct Health hp;
	struct Collider_AABB collider;
	int active;
	int hit;
	float hit_cooldown;
};

void render();
int display_splash();
void check_input();
void draw_player();
void process_bullets();
int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2);
CP_Vector generate_random_pos();

const int win_width = 1280;
const int win_height = 720;
const float splash_duration = 2.0f;
char fps_str[10];

const float max_velocity = 10.0f; //pixels per second
const int speed = 10;

const int bullet_speed = 1000;
const float fire_rate = 300.0f; //bullets per minute
float shoot_cooldown = 0.0f;
float hurt_window = 0.1f; //seconds

CP_Image splash;
CP_Image player_sprite;
CP_Image bullet_sprite;
CP_Image enemy_sprite;
CP_Image enemy_hurt_sprite;
CP_Image health_bar_sprite;

//player
CP_Vector pos;
CP_Vector velocity;
float player_width;
float player_height;

//health bar
float bar_width = 200;
float bar_height = 20;

//bounds
float xbounds;
float ybounds;

float bullet_width;
float bullet_height;

float enemy_width;
float enemy_height;

struct Bullet arr_bullet[999];
struct Enemy arr_enemy[5];
//struct Enemy enemy;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	srand((int)time(0)); //random seed
	CP_System_SetWindowSize(win_width, win_height);

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_Settings_TextSize(50);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_System_SetFrameRate(60);

	splash = CP_Image_Load("./Assets/DigiPen_BLACK.png");
	player_sprite = CP_Image_Load("./Assets/dude.png");
	bullet_sprite = CP_Image_Load("./Assets/bullet.png");
	enemy_sprite = CP_Image_Load("./Assets/enemy.png");
	health_bar_sprite = CP_Image_Load("./Assets/healthbar.png");

	pos = CP_Vector_Set((float)win_width / 2, (float)win_height / 2);
	velocity = CP_Vector_Set(0.0f, 0.0f);

	player_width = (float)CP_Image_GetWidth(player_sprite) * 2;
	player_height = (float)CP_Image_GetHeight(player_sprite) * 2;

	bullet_width = (float)CP_Image_GetWidth(bullet_sprite);
	bullet_height = (float)CP_Image_GetHeight(bullet_sprite);

	enemy_width = (float)CP_Image_GetWidth(enemy_sprite) * 3;
	enemy_height = (float)CP_Image_GetHeight(enemy_sprite) * 3;

	xbounds = win_width - player_width / 2;
	ybounds = win_height - player_height / 2;

	unsigned char *pixels = malloc(CP_Image_GetPixelBufferSize(enemy_sprite));
	CP_Image_GetPixelData(enemy_sprite, pixels);

	//Create Enemy Hurt Sprite from modified enemy_sprite pixel data.
	if (pixels)
	{
		for (int i = 0; i < CP_Image_GetPixelBufferSize(enemy_sprite); ++i)
		{
			if (i % 4 == 3) //alpha
			{
				continue;
			}

			if (i % 4 == 0) //red
			{
				if (pixels[i - 1] > 0)
					pixels[i - 1] = 255;
			}
			else
				pixels[i] = 0;

		}

	}
	enemy_hurt_sprite = CP_Image_CreateFromData(CP_Image_GetWidth(enemy_sprite), CP_Image_GetHeight(enemy_sprite), pixels);

	//init bullets
	for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
	{
		struct Bullet bullet = arr_bullet[i];
		bullet.active = 0;
		bullet.pos = CP_Vector_Set(-1, -1);
		bullet.velocity = CP_Vector_Set(0, 0);

		bullet.collider.width = (int)bullet_width;
		bullet.collider.height = (int)bullet_height;

		arr_bullet[i] = bullet;
	}

	for (int i = 0; i < sizeof(arr_enemy) / sizeof(arr_enemy[0]); i++)
	{
		//test enemy
		struct Enemy enemy = arr_enemy[i];
		enemy.pos = generate_random_pos();
		enemy.active = 1;
		enemy.hp.max = 100;
		enemy.hp.current = enemy.hp.max;

		enemy.collider.width = (int)enemy_width;
		enemy.collider.height = (int)enemy_height;

		arr_enemy[i] = enemy;

	}

}

int display_splash()
{
	//splash
	if (CP_System_GetSeconds() < splash_duration)
	{
		CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
		CP_Image_Draw(splash, win_width / 2.0f, win_height / 2.0f, (float)CP_Image_GetWidth(splash), (float)CP_Image_GetHeight(splash), 255);
		return 1;
	}
	return 0;
}

void process_bullets()
{
	//bullet
	for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active)
		{
			if ((bullet.pos.x > win_width || bullet.pos.x < 0) && (bullet.pos.y > win_height || bullet.pos.y < 0))
			{
				bullet.active = 0;
				bullet.pos = CP_Vector_Set(-1, -1);
				bullet.velocity = CP_Vector_Set(0, 0);

				arr_bullet[i] = bullet;
				continue;
			}

			for (int j = 0; j < sizeof(arr_enemy) / sizeof(arr_enemy[0]); j++)
			{
				if (!arr_enemy[j].active)
					continue;

				struct Enemy *enemy = &arr_enemy[j];
				if (check_collision_AABB(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
				{
					bullet.active = 0;
					bullet.pos = CP_Vector_Set(-1, -1);
					bullet.velocity = CP_Vector_Set(0, 0);

					if (!enemy->hit)
					{
						enemy->hit = 1;
						enemy->hp.current -= 10;
					}
				}
			}

			bullet.pos = CP_Vector_Add(bullet.pos, CP_Vector_Scale(bullet.velocity, CP_System_GetDt()));
			arr_bullet[i] = bullet;
		}

	}
}

CP_Vector generate_random_pos()
{
	float x = (float) (rand() % win_width);
	float y = (float) (rand() % win_height);

	return CP_Vector_Set(x, y);
}

int check_collision_AABB(struct Collider_AABB collider1, CP_Vector pos1, struct Collider_AABB collider2, CP_Vector pos2)
{
	//simple collision
	int is_overlap_x = (pos1.x + collider1.width >= pos2.x - collider2.width / 2 && pos2.x + collider2.width / 2 >= pos1.x - collider1.width);
	int is_overlap_y = (pos1.y + collider1.height >= pos2.y - collider2.height / 2 && pos2.y + collider2.height / 2 >= pos1.y - collider1.height);

	if (is_overlap_x && is_overlap_y)
		return 1;

	return 0;
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// check input, update simulation, render etc.
	if (display_splash())
		return;

	check_input();

	if (shoot_cooldown < 0)
		shoot_cooldown = 0;
	else
		shoot_cooldown -= CP_System_GetDt();

	process_bullets();

	//Process enemies
	for (int i = 0; i < sizeof(arr_enemy) / sizeof(arr_enemy[0]); i++)
	{
		struct Enemy* enemy = &arr_enemy[i];
		if (enemy->hit)
		{
			enemy->hit_cooldown -= CP_System_GetDt();
			if (enemy->hit_cooldown <= 0)
			{
				enemy->hit = 0;
				enemy->hit_cooldown = hurt_window;
			}
		}

		if (enemy->hp.current <= 0)
		{
			enemy->active = 0;
		}

	}

	render();

}

void check_input()
{
	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity.y -= speed;
		pos.y -= speed;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		//velocity.y += speed;
		pos.y += speed;
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		//velocity.x -= speed;
		pos.x -= speed;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		//velocity.x += speed;
		pos.x += speed;
	}

	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		if (shoot_cooldown > 0)
			return;

		shoot_cooldown = 60 / fire_rate; //seconds per bullet

		float mouseX = CP_Input_GetMouseX();
		float mouseY = CP_Input_GetMouseY();

		CP_Vector mousePos = CP_Vector_Set(mouseX, mouseY);
		CP_Vector shoot_direction = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, pos));

		for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
		{
			struct Bullet bullet = arr_bullet[i];
			if (!bullet.active) {
				bullet.pos = CP_Vector_Set(pos.x, pos.y);
				bullet.velocity = CP_Vector_Set(shoot_direction.x * bullet_speed, shoot_direction.y * bullet_speed);
				bullet.active = 1;

				arr_bullet[i] = bullet;
				break;
			}
		}

	}
}

void render()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("uwu", (float)win_width / 2, (float)win_height / 2);

	//Get FPS
	float fps = roundf(CP_System_GetFrameRate());
	sprintf_s(fps_str, 10, "%d", (int)fps);

	//Display FPS
	CP_Font_DrawText(fps_str, 100, 100);

	//Render Bullets
	for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active) {
			CP_Image_Draw(bullet_sprite, bullet.pos.x, bullet.pos.y, bullet_width, bullet_height, 255);
		}
	}

	//Render Enemies
	for (int i = 0; i < sizeof(arr_enemy) / sizeof(arr_enemy[0]); i++)
	{
		struct Enemy enemy = arr_enemy[i];
		if (enemy.active)
		{
			CP_Image_Draw(enemy_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			float percent = enemy.hp.current / enemy.hp.max;
			CP_Image_Draw(health_bar_sprite, enemy.pos.x, enemy.pos.y - 100, percent * bar_width, bar_height, 255);

			if (enemy.hit)
			{
				CP_Image_Draw(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 135);
			}
		}
	}

	draw_player();

}

void draw_player()
{
	CP_Image_Draw(player_sprite, pos.x, pos.y, player_width, player_height, 255);
	if (pos.x > win_width - player_width / 2) //x-max
	{
		float new_x = 0 - (win_width - pos.x);
		CP_Image_Draw(player_sprite, new_x, pos.y, player_width, player_height, 255);
		if (pos.x > win_width)
			pos.x = 0;
	}
	else if (pos.x < 0 + player_width / 2) //x-min
	{
		float new_x = win_width + pos.x;
		CP_Image_Draw(player_sprite, new_x, pos.y, player_width, player_height, 255);
		if (pos.x <= 0)
			pos.x = (float)win_width;
	}

	if (pos.y > win_height - player_height / 2) //y-max
	{
		float new_y = 0 - (win_height - pos.y);
		CP_Image_Draw(player_sprite, pos.x, new_y, player_width, player_height, 255);
		if (pos.y > win_height)
			pos.y = 0;
	}
	else if (pos.y < 0 + player_height / 2) //y-min
	{
		float new_y = win_height + pos.y;
		CP_Image_Draw(player_sprite, pos.x, new_y, player_width, player_height, 255);
		if (pos.y <= 0)
			pos.y = (float)win_height;
	}
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
