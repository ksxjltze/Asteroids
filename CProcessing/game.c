#pragma once
#include "game.h"
#include "constants.h"


char fps_str[10];
float shoot_cooldown = 0.0f;

CP_Image player_sprite;
CP_Image bullet_sprite;
CP_Image enemy_sprite;
CP_Image enemy_hurt_sprite;
CP_Image health_bar_sprite;
CP_Image player_health_sprite;
CP_Image powerups_sprite;

//player
CP_Vector pos;
CP_Vector velocity;
float player_width;
float player_height;

float bullet_width;
float bullet_height;

float enemy_width;
float enemy_height;

float powerups_width;
float powerups_height;

struct Bullet arr_bullet[999];
struct Enemy arr_enemy[5];
struct Heart arr_heart[3];
struct powerups arr_powerups[2];
//struct Enemy enemy;

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	settings_setup(WIN_WIDTH, WIN_HEIGHT);
	load_sprites();
	init_entities();
}

void init_entities()
{
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

		powerups.collider.width = (int)powerups_width;
		powerups.collider.height = (int)powerups_height;

		arr_powerups[i] = powerups;

	}

}

void load_sprites()
{
	player_sprite = CP_Image_Load(PLAYER_SPRITE_PATH);
	bullet_sprite = CP_Image_Load("./Assets/bullet.png");
	enemy_sprite = CP_Image_Load("./Assets/enemy.png");
	health_bar_sprite = CP_Image_Load("./Assets/healthbar.png");
	powerups_sprite = CP_Image_Load("./Assets/powerup.png");
	enemy_hurt_sprite = generate_hurt_sprite(enemy_sprite);
	player_health_sprite = CP_Image_Load("./Assets/heart.png");

	pos = CP_Vector_Set((float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);
	velocity = CP_Vector_Set(0.0f, 0.0f);

	player_width = (float)CP_Image_GetWidth(player_sprite) * 2;
	player_height = (float)CP_Image_GetHeight(player_sprite) * 2;

	bullet_width = (float)CP_Image_GetWidth(bullet_sprite);
	bullet_height = (float)CP_Image_GetHeight(bullet_sprite);

	enemy_width = (float)CP_Image_GetWidth(enemy_sprite) * 3;
	enemy_height = (float)CP_Image_GetHeight(enemy_sprite) * 3;

	powerups_width = (float)CP_Image_GetWidth(powerups_sprite) * 0.3f;
	powerups_height = (float)CP_Image_GetWidth(powerups_sprite) * 0.3f;
}

CP_Image generate_hurt_sprite(CP_Image sprite)
{

	unsigned char* pixels = malloc(CP_Image_GetPixelBufferSize(enemy_sprite));
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

	return CP_Image_CreateFromData(CP_Image_GetWidth(enemy_sprite), CP_Image_GetHeight(enemy_sprite), pixels);
}

void process_bullets()
{
	//bullet
	for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
	{
		struct Bullet bullet = arr_bullet[i];
		if (bullet.active)
		{
			if ((bullet.pos.x > WIN_WIDTH || bullet.pos.x < 0) && (bullet.pos.y > WIN_HEIGHT || bullet.pos.y < 0))
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

				struct Enemy* enemy = &arr_enemy[j];
				if (check_collision_AABB(bullet.collider, bullet.pos, enemy->collider, enemy->pos))
				{
					bullet.active = 0;
					bullet.pos = CP_Vector_Set(-1, -1);
					bullet.velocity = CP_Vector_Set(0, 0);

					if (!enemy->status.hit)
					{
						enemy->status.hit = 1;
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
	float x = (float)(rand() % WIN_WIDTH);
	float y = (float)(rand() % WIN_HEIGHT);

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
	check_input();

	if (shoot_cooldown < 0)
		shoot_cooldown = 0;
	else
		shoot_cooldown -= CP_System_GetDt();

	//Process enemies
	for (int i = 0; i < sizeof(arr_enemy) / sizeof(arr_enemy[0]); i++)
	{
		struct Enemy* enemy = &arr_enemy[i];
		if (enemy->status.hit)
		{
			enemy->status.hit_cooldown -= CP_System_GetDt();
			if (enemy->status.hit_cooldown <= 0)
			{
				enemy->status.hit = 0;
				enemy->status.hit_cooldown = HURT_WINDOW;
			}
		}

		if (enemy->hp.current <= 0)
		{
			enemy->active = 0;
		}

	}

	process_bullets();

	render();

}

void check_input()
{
	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity.y -= speed;
		pos.y -= SPEED;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		//velocity.y += speed;
		pos.y += SPEED;
	}

	if (CP_Input_KeyDown(KEY_A))
	{
		//velocity.x -= speed;
		pos.x -= SPEED;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		//velocity.x += speed;
		pos.x += SPEED;
	}

	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		if (shoot_cooldown > 0)
			return;

		shoot_cooldown = 60 / FIRE_RATE; //seconds per bullet

		float mouseX = CP_Input_GetMouseX();
		float mouseY = CP_Input_GetMouseY();

		CP_Vector mousePos = CP_Vector_Set(mouseX, mouseY);
		CP_Vector shoot_direction = CP_Vector_Normalize(CP_Vector_Subtract(mousePos, pos));

		for (int i = 0; i < sizeof(arr_bullet) / sizeof(arr_bullet[0]); i++)
		{
			struct Bullet bullet = arr_bullet[i];
			if (!bullet.active) {
				bullet.pos = CP_Vector_Set(pos.x, pos.y);
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
	//Get FPS
	float fps = roundf(CP_System_GetFrameRate());
	sprintf_s(fps_str, 10, "%d", (int)fps);

	//Display FPS
	CP_Font_DrawText(fps_str, 100, 100);
}

void render()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Asteroids", (float)WIN_WIDTH / 2, (float)WIN_HEIGHT / 2);

	display_fps();

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
			CP_Image_Draw(health_bar_sprite, enemy.pos.x, enemy.pos.y - 100, percent * BAR_WIDTH, BAR_HEIGHT, 255);

			if (enemy.status.hit)
			{
				CP_Image_Draw(enemy_hurt_sprite, enemy.pos.x, enemy.pos.y, enemy_width, enemy_height, 255);
			}
		}
	}

	// render powerups
	for (int i = 0; i < sizeof(arr_powerups) / sizeof(arr_powerups[0]); i++)
	{
		struct powerups powerups = arr_powerups[i];
		if (powerups.active)
		{
			CP_Image_Draw(powerups_sprite, powerups.pos.x, powerups.pos.y, powerups_width, powerups_height, 255);
		}

	}

	draw_player();

	//Draw Hearts
	for (int i = 0; i < sizeof(arr_heart) / sizeof(arr_heart[0]); i++)
	{
		if (arr_heart[i].active == 1)
		{
			CP_Image_Draw(player_health_sprite, arr_heart[i].pos.x, arr_heart[i].pos.y, (float)CP_Image_GetWidth(player_health_sprite) * 2,
				(float)CP_Image_GetHeight(player_health_sprite), 255);
		}
	}

}

void draw_player()
{
	CP_Image_Draw(player_sprite, pos.x, pos.y, player_width, player_height, 255);
	if (pos.x > WIN_WIDTH - player_width / 2) //x-max
	{
		float new_x = 0 - (WIN_WIDTH - pos.x);
		CP_Image_Draw(player_sprite, new_x, pos.y, player_width, player_height, 255);
		if (pos.x > WIN_WIDTH)
			pos.x = 0;
	}
	else if (pos.x < 0 + player_width / 2) //x-min
	{
		float new_x = WIN_WIDTH + pos.x;
		CP_Image_Draw(player_sprite, new_x, pos.y, player_width, player_height, 255);
		if (pos.x <= 0)
			pos.x = (float)WIN_WIDTH;
	}

	if (pos.y > WIN_HEIGHT - player_height / 2) //y-max
	{
		float new_y = 0 - (WIN_HEIGHT - pos.y);
		CP_Image_Draw(player_sprite, pos.x, new_y, player_width, player_height, 255);
		if (pos.y > WIN_HEIGHT)
			pos.y = 0;
	}
	else if (pos.y < 0 + player_height / 2) //y-min
	{
		float new_y = WIN_HEIGHT + pos.y;
		CP_Image_Draw(player_sprite, pos.x, new_y, player_width, player_height, 255);
		if (pos.y <= 0)
			pos.y = (float)WIN_HEIGHT;
	}
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}